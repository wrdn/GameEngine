#pragma once

#include "float3.h"
#include "Quaternion.h"
#include "Material.h"
#include "Mesh.h"

class GraphicsObject
{
private:

	// globally disable use of shaders and textures (allows easy overriding without modifying objects)
	// these do not effect local state when changed, so if GLOBAL_USE_TEXTURES=true, but local_use_textures=false,
	// the object will not use textures. Both initially true
	static bool GLOBAL_USE_SHADERS;
	static bool GLOBAL_USE_TEXTURES;

	// scale is non-uniform, orientation is amount of rotation (in degrees) around cardinal XYZ axis
	float3 position, scale, orientation;
	MeshHandle mesh; // shared_ptr to mesh (which should be managed in ResourceManager)

	Material objectMaterial;

	bool local_use_textures;
	bool local_use_shaders;

	GraphicsObject() : local_use_textures(true), local_use_shaders(true) {};
};
bool GraphicsObject::GLOBAL_USE_SHADERS = true;
bool GraphicsObject::GLOBAL_USE_TEXTURES = true;