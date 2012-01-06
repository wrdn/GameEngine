#pragma once

#include "float3.h"
#include "Namable.h"

enum CameraProjectionType { Perspective, Orthographic };
class Camera : public Namable
{
public:
	f32 fov, nearPlane, farPlane;
	float3 position, target, up;
	bool isStatic;
	CameraProjectionType projectionType;
	f32 speed;

	Camera() : fov(45), nearPlane(0.1f), farPlane(100), position(0,0,0), target(0,0,-1), up(0,1,0), isStatic(false), projectionType(Perspective), speed(2) {};
	Camera(const f32 _fov, const f32 _near, const f32 _far, const float3& _position, const float3& _target, const float3& _up, bool _isStatic, CameraProjectionType ptype)
		: fov(_fov), nearPlane(_near), farPlane(_far), position(_position), target(_target), up(_up), isStatic(_isStatic), projectionType(ptype), speed() {};
};