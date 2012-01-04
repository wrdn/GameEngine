#pragma once
#include "ctypes.h"
#include <rapidxml.hpp>
#include <vector>
#include <string>
#include "float3.h"

#define EngineConfigVersion "1.0" // config "version" flag must equal this
#define MINIMUM_MEMORY_ALLOC 128U // note: "U" denotes unsigned integer

class Namable // Debug functionality - inherited item can be given a name (useful for debugging)
{
private:
#ifdef _DEBUG
	std::string name;
public:
	void SetName(const std::string &m) { name = m; }
	std::string &GetName() { return name; }
#else
#define SetName(m)
#define GetName() ""
#endif
};

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

class EngineConfig // parses the engine/scene config file
{
private:
	// [Global Engine Options]
	u32 maxMemoryAlloc; // max memory the engine can use in MB (default=128MB)
	
	u32 activeCameraIndex; // clamp to [0, cameras.size()-1]
	std::vector<Camera> cameras;


	// Pass it the node <global>
	void ParseGlobalOptions(rapidxml::xml_node<> *base_global_node);
	void ParseCameraOptions(rapidxml::xml_node<> *base_camera_node);

public:
	bool ParseConfigFile(const c8* xml_config_filename);

	EngineConfig() : maxMemoryAlloc(MINIMUM_MEMORY_ALLOC), activeCameraIndex(0) {};
	~EngineConfig() {};
};