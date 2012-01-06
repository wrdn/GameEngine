#pragma once
#include "color.h"
#include "Light.h"
#include "Camera.h"
#include "float2.h"
#include <rapidxml.hpp>
#include <string>
#include <vector>

class EngineConfig // parses the engine/scene config file
{
private:
	static const u32 MINIMUM_MEMORY_ALLOC = 128U;
	static const c8* EngineConfigVersion; // 1.0
	static const u32 DEFAULT_RES_WIDTH = 640U, DEFAULT_RES_HEIGHT = 480U;

	// [Global Engine Options]
	u32 maxMemoryAlloc; // max memory the engine can use in MB (default=128MB)
	vec2i resolution;

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
	// Global
	u32 GetMaxMemoryAlloc() const { return maxMemoryAlloc; }
	const vec2i& GetResolution() const { return resolution; }

	// Cameras
	u32 GetActiveCameraIndex() const { return activeCameraIndex; }
	const std::vector<Camera> &GetCameras() const { return cameras; }

	// Lights
	const std::vector<Light>& GetLights() const { return lights; }

	bool ParseConfigFile(const c8* xml_config_filename);

	EngineConfig()
		: maxMemoryAlloc(MINIMUM_MEMORY_ALLOC), resolution(DEFAULT_RES_WIDTH, DEFAULT_RES_HEIGHT), activeCameraIndex(0) {};
	~EngineConfig() {};
};
