#pragma once

#pragma warning (disable : 4100) // not all functions below need clientData, this gets rid of warning "unreferenced formal parameter"

#include <AntTweakBar.h>
#include "ctypes.h"
#include "util.h"
#include <GL/freeglut.h>

f32 teapotRotationInterpolationFactor=0;
bool automaticTeapotRotation=true;

void TW_CALL SetTeapotInterpolationFactor(const void *value, void *clientData)
{
	*(f32*)clientData = clamp( (*(f32*)value)/100.0f ,0.0f,1.0f); // clamp value/100 to 0 to 1 range
}
void TW_CALL GetTeapotInterpolationFactor(void *value, void *clientData)
{ 
	*(f32 *)value = teapotRotationInterpolationFactor;
}
void setup_anttweakbar(TwBar *mainBar)
{
	TwInit(TW_OPENGL, NULL);
	TwWindowSize(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	mainBar = TwNewBar("Main");
	TwAddVarCB(mainBar, "Teapot Interpolation Factor", TW_TYPE_FLOAT, SetTeapotInterpolationFactor, GetTeapotInterpolationFactor, &teapotRotationInterpolationFactor, 0);
	TwAddVarRW(mainBar, "Teapot Automatic Rotation", TW_TYPE_BOOL32, &automaticTeapotRotation, 0);
};
void OnMouseMotion(i32 mouseX, i32 mouseY)
{
	TwEventMouseMotionGLUT(mouseX, mouseY);
}
void OnMouseButton(i32 glutButton, i32 glutState, i32 mouseX, i32 mouseY)
{
	TwEventMouseButtonGLUT(glutButton, glutState, mouseX, mouseY);
}
void OnSpecialEvent(i32 glutKey, i32 mouseX, i32 mouseY)
{
	TwEventSpecialGLUT(glutKey,mouseX,mouseY);
}