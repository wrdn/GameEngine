#pragma once
#include "ctypes.h"
#include <rapidxml.hpp>
#include <string>
#include "float3.h"
#include "color.h"
#include <vector>

class Namable // Debug functionality - inherited item can be given a name (useful for debugging)
{
#ifdef _DEBUG
private:
	std::string name;
public:
	inline void SetName(const std::string &m) { name = m; };
	inline const std::string &GetName() { return name; };
#else
public:
	inline void SetName(const std::string &m) { if(m.size()){} };
	inline const std::string GetName() { return ""; };
#endif
};

#define EngineConfigVersion "1.0" // config "version" flag must equal this
#define MINIMUM_MEMORY_ALLOC 128U // note: "U" denotes unsigned integer

enum CameraProjectionType { Perspective, Orthographic };
class Camera : public Namable
{
public:
	f32 fov, nearPlane, farPlane;
	float3 position, target, up;
	bool isStatic;
	CameraProjectionType projectionType;

	Camera() : fov(45), nearPlane(0.1f), farPlane(100), position(0,0,0), target(0,0,-1), up(0,1,0), isStatic(false), projectionType(Perspective) {};
	Camera(const f32 _fov, const f32 _near, const f32 _far, const float3& _position, const float3& _target, const float3& _up, bool _isStatic, CameraProjectionType ptype)
		: fov(_fov), nearPlane(_near), farPlane(_far), position(_position), target(_target), up(_up), isStatic(_isStatic), projectionType(ptype) {};
};

enum LightType { Point, Directional, Spot };
class Light
{
public:
	LightType lightType;
	color ambientColor, diffuseColor, specularColor; // shared by all lights 
	float4 position; // point/directional light (w=1|0 respectively)
	float3 spotDirection; f32 spotCutoffAngle; // spotlights only

	Light() : lightType(Directional), ambientColor(GREY), diffuseColor(GREY), specularColor(GREY), position(), spotDirection(), spotCutoffAngle(20) {}; // default parameters (empty constructor)
	
	Light(LightType _lightType, const color &amb, const color &diff, const color &spec, const float4& pos) // point/directional light (colors + position)
		: lightType(_lightType), ambientColor(amb), diffuseColor(diff), specularColor(spec), position(pos), spotDirection(), spotCutoffAngle(20) {};

	Light(LightType _lightType, const color &amb, const color &diff, const color &spec, const float4& pos, const float3& spotDir, const f32 spotCutoff) // spotlight (colors + position + spot direction + cutoff)
		: lightType(_lightType), ambientColor(amb), diffuseColor(diff), specularColor(spec), position(pos), spotDirection(spotDir), spotCutoffAngle(spotCutoff) {};
	
	~Light() {};
};

class EngineConfig // parses the engine/scene config file
{
private:
	// [Global Engine Options]
	u32 maxMemoryAlloc; // max memory the engine can use in MB (default=128MB)
	
	// [Camera Options]
	u32 activeCameraIndex; // clamp to [0, cameras.size()-1]
	std::vector<Camera> cameras;

	// [Lights]
	std::vector<Light> lights;

	// Parse functions
	void ParseGlobalOptions(rapidxml::xml_node<> *base_global_node);
	void ParseCameras(rapidxml::xml_node<> *base_camera_node);

	// note: only position is required for a light (if not provided, the light is ignored).
	// every other option can recieve a default value
	void ParseLights(rapidxml::xml_node<> *base_lights_node);

public:
	bool ParseConfigFile(const c8* xml_config_filename);

	EngineConfig() : maxMemoryAlloc(MINIMUM_MEMORY_ALLOC), activeCameraIndex(0) {};
	~EngineConfig() {};
};