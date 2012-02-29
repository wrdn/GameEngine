#pragma once

#include <GL/glew.h>
#include "float3.h"
#include "float2.h"
#include "Resource.h"

#include <memory>

const GLvoid* BUFFER_OFFSET(const u32 i);

struct MeshVBO
{
public:
	u32 meshData;
	u32 indexData;
	
	MeshVBO() : meshData(0), indexData(0) {};
};

const u32 VERTEX_POSITION_BUFFER_OFFSET = 0; // at start of struct
const u32 VERTEX_NORMAL_BUFFER_OFFSET = 12; // 0 + sizeof(float3) == 0+position
const u32 VERTEX_UV_BUFFER_OFFSET = 24; // 0 + sizeof(float3) + sizeof(float3) == 0+position+normal

struct VERTEX // 32 bytes
{
public:
	float3 position, normal;
	float2 uv;

	VERTEX() {};
	VERTEX(const float3 &_position, const float3 &_normal, const float2 &_uv)
		: position(_position), normal(_normal), uv(_uv) {}; 
};

class Mesh : public Resource
{
private:
	MeshVBO meshvbo;
	GLenum geometryDataFormat; // GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_QUADS, GL_POINTS etc 
	
	u32 dbg_vertex_array_sz, dbg_index_array_sz;
public:
	Mesh() : geometryDataFormat(GL_TRIANGLES), dbg_vertex_array_sz(0),
				dbg_index_array_sz(0) {};
	~Mesh() { Unload(); };
	
	GLenum GetGeometryDataFormat() const { return geometryDataFormat; };
	void SetGeometryDataFormat(const GLenum dataFormat) // usually GL_TRIANGLES, but can change e.g. to GL_QUADS, GL_POINTS, GL_TRIANGLE_STRIP etc
	{
		geometryDataFormat = dataFormat;
	};
	
	bool Valid() const { return meshvbo.meshData > 0 && meshvbo.indexData > 0; };
	
	void Unload();
	bool BuildVBO(const VERTEX *vertexData, const u32 vertexArraySz, const u32 *indexData, const u32 indexArraySz);
	void Draw() const;
};

typedef std::shared_ptr<Mesh> MeshHandle;