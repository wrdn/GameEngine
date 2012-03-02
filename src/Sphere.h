#pragma once

#include "GraphicsObject.h"
#include "ResourceManager.h"
#include <cmath>

class Sphere : public GraphicsObject
{
private:
	f32 radius;
	u32 slices, stacks;

public:
	Sphere() : radius(1), slices(10), stacks(10) {};

	f32 GetRadius() const { return radius; };
	u32 GetSlices() const { return slices; };
	u32 GetStacks() const { return stacks; };

	bool Create(f32 _radius, u32 _slices, u32 _stacks)
	{
		radius = _radius;
		slices = _slices;
		stacks = _stacks;

		int vertexesToUse = stacks*slices;
		int indexesToUse = vertexesToUse*6;

		VERTEX *vertexData = new VERTEX[vertexesToUse];
		u32 *indexData = new u32[indexesToUse];

		int vertexCount=0;

		for(u32 x=0;x<slices;++x)
		{
			for(u32 y=0;y<stacks;++y)
			{
				float angleA = ((float)x/(float)(slices-1))*2*PI;
				float angleB = ((float)y/(float)(stacks-1))*PI;
				
				float xOff = radius * sin(angleA) * sin(angleB);
				float yOff = radius * cos(angleA) * sin(angleB);
				float zOff = radius * cos(angleB);

				float3 pos(xOff, yOff, zOff);
				VERTEX v(pos, pos.normalize(), float2(xOff, yOff));
				vertexData[vertexCount++] = v;
			}
		}

		u32 indexCount=0;

		for(u32 y=0;y<stacks;y++)
		{
			for(u32 x=0;x<slices;x++)
			{
				int i = x+((slices)*y);
				int iplus1 = i+1;
				int islices = i+slices;
				int islices1 = islices+1;

				indexData[indexCount++] = iplus1;
				indexData[indexCount++] = islices1;
				indexData[indexCount++] = islices;

				indexData[indexCount++] = i;
				indexData[indexCount++] = iplus1;
				indexData[indexCount++] = islices;
			}
		}

		MeshHandle mh = ResourceManager::get().CreateAndGetResource<Mesh>();
		mh->SetName("sphere"); // useful for debugging
		bool builtVBO = mh->BuildVBO(vertexData, vertexCount, indexData, indexCount);
		SetMesh(mh);

		delete [] vertexData;
		delete [] indexData;

		return builtVBO;
	};

	//bool Create(f32 _radius, u32 _slices, u32 _stacks)
	//{
	//	if( ( _stacks < 2 ) && ( _slices < 2 ) ) return false;

	//	radius = _radius;
	//	slices = _slices;
	//	stacks = _stacks;

	//	f32 stack_increment = 1.0f / (f32)stacks; // y
	//	f32 slice_increment = PI*2.0f / (f32)slices; // x
	//	f32 x,y,z;
	//	u32 vertexCount=0; u32 indexCount=0;
	//	u32 arraySize = (slices+1)*(stacks-1)+2;
	//	VERTEX *verts = new VERTEX[arraySize];

	//	// Top
	//	VERTEX top;
	//	top.position = float3(0, radius, 0);
	//	top.normal = float3(0, 1, 0);
	//	top.uv = float2(0, 1);
	//	verts[vertexCount] = top;
	//	++vertexCount;

	//	// Bottom
	//	VERTEX bottom;
	//	bottom.position = float3(0, -radius, 0);
	//	bottom.normal = float3(0, -1, 0);
	//	bottom.uv = float2::ZERO;
	//	verts[vertexCount] = bottom;
	//	++vertexCount;

	//	for( u32 i = 1; i < stacks; ++i )
	//	{
	//		y = sin(PI*(1/2.0f - stack_increment * (f32)i));
	//		f32 temp_radius = cos(PI*(1/2.0f - stack_increment * (f32)i));
	//		f32 temp_tex = 1.0f - stack_increment * (f32)i;
	//		u32 temp_vcount = vertexCount;

	//		// Create vertices around the sphere (slices)
	//		for( u32 j = 0; j < slices; ++j )
	//		{
	//			x = cos((f32)j * slice_increment);
	//			z = -sin((f32)j*slice_increment);

	//			VERTEX v(
	//				float3(radius*temp_radius*x, radius*y, radius*temp_radius*z),
	//				float3(temp_radius*x, y, temp_radius*z),
	//				float2((f32)j/(f32)slices, temp_tex));
	//			verts[vertexCount] = v;
	//			++vertexCount;
	//		}
	//		VERTEX lv = verts[temp_vcount];
	//		lv.uv.y(temp_tex);
	//		verts[vertexCount] = lv;
	//		++vertexCount;
	//	}


	//	indexCount = 0;
	//	vertexCount = 2;

	//	u32 indicesArraySz = ((2+(stacks-1)*(slices+1)*2) * 3) - 6;
	//	u32 *indicesArray = new u32[indicesArraySz];
	//	u32 index=0;

	//	// Top
	//	for(u32 j=0; j < slices; ++j)
	//	{
	//		indicesArray[index++] = 0;
	//		indicesArray[index++] = vertexCount;
	//		indicesArray[index++] = vertexCount+1;
	//		++vertexCount;
	//	}

	//	vertexCount -= (slices);

	//	// Middle (stacks)
	//	for(u32 i=0;i<(stacks-2); ++i)
	//	{
	//		for(u32 j=0;j<=slices;++j)
	//		{
	//			indicesArray[index++] = vertexCount;
	//			indicesArray[index++] = slices+vertexCount;
	//			indicesArray[index++] = slices+vertexCount+1;

	//			indicesArray[index++] = vertexCount;
	//			indicesArray[index++] = slices+vertexCount+1;
	//			indicesArray[index++] = vertexCount+1;

	//			++vertexCount;
	//		}
	//	}

	//	// Bottom
	//	for(u32 j=0; j <= slices; ++j)
	//	{
	//		indicesArray[index++] = 1;
	//		indicesArray[index++] = vertexCount+slices-j;
	//		indicesArray[index++] = vertexCount+slices-j-1;
	//	}

	//	MeshHandle mh = ResourceManager::get().CreateAndGetResource<Mesh>();
	//	mh->SetName("sphere"); // useful for debugging
	//	bool builtVBO = mh->BuildVBO(verts, vertexCount, indicesArray, indicesArraySz);
	//	SetMesh(mh);

	//	delete [] verts;
	//	delete [] indicesArray;

	//	return builtVBO;
	//};
};