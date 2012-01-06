#pragma once

#include "float3.h"

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