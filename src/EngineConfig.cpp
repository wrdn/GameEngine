#include "EngineConfig.h"
#include "util.h"
#include "strutils.h"
#include <sstream> // helps with streaming into types
#include <string.h>
#include "float4.h"
#include "float2.h"

using namespace std;
using namespace rapidxml;

const c8* EngineConfig::EngineConfigVersion = "1.0";

#define CASE_INSENSITIVE 0U,false // used in first_node, first_attribute etc.
#define CASE_SENSITIVE 0U,true

template <class T> bool GreaterThanZero(T &src) { return src>0; };
template <class T> bool GreaterThanOrEqualToZero(T &src) { return src>=0; };
template <class T> bool LessThanZero(T &src) { return src<0; };
template <class T> bool LessThanOrEqualToZero(T &src) { return src<=0; };

template <class T>
bool _xml_parse_v(xml_node<> *m, T &output_var, bool (*CRes)(T&)=0)
{
	if(m)
	{
		T val;
		stringstream tmps(m->value());
		tmps >> val;
		if(!tmps.fail())
		{
			if(CRes)
			{
				if(!CRes(val))
				{
					return false;
				}
			}

			output_var = val;
			return true;
		}
	}
	return false;
};

void EngineConfig::ParseLights(rapidxml::xml_node<> *base_lights_node)
{
	if(!base_lights_node) return;

	xml_node<> *flight = base_lights_node->first_node("light", CASE_INSENSITIVE);
	while(flight)
	{
		Light lt;

		// position required
		if(!_xml_parse_v<float4>(flight->first_node("position", CASE_INSENSITIVE), lt.position))
		{
			flight = flight->next_sibling("light", CASE_INSENSITIVE);
			continue;
		}

		_xml_parse_v<color>(flight->first_node("amb", CASE_INSENSITIVE), lt.ambientColor);
		_xml_parse_v<color>(flight->first_node("diff", CASE_INSENSITIVE), lt.diffuseColor);
		_xml_parse_v<color>(flight->first_node("spec", CASE_INSENSITIVE), lt.specularColor);

		if(_xml_parse_v<float3>(flight->first_node("spot_direction", CASE_INSENSITIVE), lt.spotDirection) ||
			_xml_parse_v<f32>(flight->first_node("spot_cutoff", CASE_INSENSITIVE), lt.spotCutoffAngle))
		{
			lt.position.w(1);
			lt.lightType = Spot;
		}
		else if(NearZero(lt.position.w()))
		{
			lt.position.w(0);
			lt.lightType = Directional;
		}
		else
		{
			lt.position.w(1);
			lt.lightType = Point;
		}
		
		lights.push_back(lt);
		flight = flight->next_sibling("light", CASE_INSENSITIVE);
	}
};

void EngineConfig::ParseCameras(rapidxml::xml_node<> *base_camera_node)
{
	if(!base_camera_node) return;

	// Check each camera name against this
	xml_attribute<> *default_camera_attribute = base_camera_node->first_attribute("active", CASE_INSENSITIVE);
	const string default_camera_name = default_camera_attribute ? default_camera_attribute->value() : "";

	xml_node<> *c = base_camera_node->first_node("camera", CASE_INSENSITIVE);
	while(c)
	{
		// we need to set this in an extra variable, because in Release mode SetName() does nothing
		// Name string only stored in Debug mode, as a debugging aid
		const std::string cameraName = c->first_attribute("name", CASE_INSENSITIVE)->value();
		
		std::string cameraProjectionType = strtolower(c->first_attribute("type", CASE_INSENSITIVE)->value());

		Camera cam;
		
		// Required Nodes: position and target
		if(!_xml_parse_v<float3>(c->first_node("position", CASE_INSENSITIVE), cam.position)
			|| !_xml_parse_v<float3>(c->first_node("target", CASE_INSENSITIVE), cam.target))
		{
			c = c->next_sibling("camera", CASE_INSENSITIVE);
			continue;
		}

		if(cameraProjectionType == "orthographic") { cam.projectionType = Orthographic; }
		else { cam.projectionType = Perspective; } // most commonly used, so default to it if "orthographic" not specified


		// Optional Nodes: up, fov, static, near, far
		_xml_parse_v<float3>(c->first_node("up", CASE_INSENSITIVE), cam.up);
		_xml_parse_v<f32>(c->first_node("fov", CASE_INSENSITIVE), cam.fov);
		
		string static_str;
		if(_xml_parse_v<string>(c->first_node("static", CASE_INSENSITIVE), static_str))
			cam.isStatic = stringtobool(static_str);
		
		// Near plane and far plane must be >0
		_xml_parse_v<f32>(c->first_node("near", CASE_INSENSITIVE), cam.nearPlane, GreaterThanZero);
		_xml_parse_v<f32>(c->first_node("far", CASE_INSENSITIVE), cam.farPlane, GreaterThanZero);

		// Once here, we know the camera has been parsed successfully, so we can check the name
		// of the camera against default_camera
		cam.SetName(cameraName.c_str());
		cameras.push_back(cam);

		if(cameraName == default_camera_name)
		{
			activeCameraIndex = cameras.size()-1;
		}

		c = c->next_sibling("camera", CASE_INSENSITIVE);
	}

	// Finished processing cameras, check we managed to parse any (if not, create a default camera)
	if(!cameras.size())
	{
		activeCameraIndex = 0;
		cameras.push_back(Camera());
	}
};

void EngineConfig::ParseGlobalOptions(rapidxml::xml_node<> *base_global_node)
{
	if(!base_global_node) return;

	i32 tmpint;
	if(_xml_parse_v<i32>(base_global_node->first_node("MaxMemory"), tmpint))
		maxMemoryAlloc = (u32)max(tmpint, (i32)maxMemoryAlloc);

	vec2i res;
	if(_xml_parse_v<vec2i>(base_global_node->first_node("resolution"), res))
	{
		if(res.x > 0) resolution.x = res.x;
		if(res.y > 0) resolution.y = res.y;
	}
};

bool EngineConfig::ParseConfigFile(const c8* xml_config_filename)
{
	// Read file to buffer
	c8* srcData = read_src_fast(xml_config_filename);
	if(!srcData || !strlen(srcData)) { return false; }
	xml_document<> doc;
	doc.parse<parse_full | parse_trim_whitespace> (srcData);

	// Check root node
	xml_node<> *rootNode = doc.first_node("engine", CASE_INSENSITIVE);
	if(!rootNode) { return false; }
	c8* attr = rootNode->first_attribute("version", CASE_INSENSITIVE)->value();
	if(string(attr) != EngineConfigVersion) { return false; } // Invalid Version

	// Parse <global> options
	xml_node<> *globalNode = rootNode->first_node("global", CASE_INSENSITIVE);
	if(globalNode) ParseGlobalOptions(globalNode);

	// Parse <cameras> options
	xml_node<> *cameraNode = rootNode->first_node("cameras", CASE_INSENSITIVE);
	if(cameraNode) ParseCameras(cameraNode);
	else cameras.push_back(Camera()); // if no cameras node, push back a default camera

	// Parse key bindings
	// ...

	// Parse <lights> options
	ParseLights(rootNode->first_node("lights", CASE_INSENSITIVE));

	delete [] srcData;
	return false;
};
