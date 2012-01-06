#ifdef _WIN32
#pragma warning (disable : 4505) // used to disable warning from glut code
#endif

#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <cmath>

#include "util.h"
#include "PerfTimer.h"
#include "EngineConfig.h"
#include "GameTime.h"

#include <GL/freeglut.h>
#include <AntTweakBar.h>

#include "Quaternion.h"

void cube();
void setup_lights();

void setup_anttweakbar();


GameTime gt;
Camera c;
TwBar *mainBar;
f32 teapotRotationInterpolationFactor=0;

Quaternion originTeapotRotation;
Quaternion finalTeapotRotation;

void keyb(uc8 _key, i32 x, i32 y)
{
	if(x||y){} uc8 key = (uc8)tolower(_key);
	if(key == 'q') { glutLeaveMainLoop(); return; }
};

f32 angle=0, ltangle=0;
f32 mfactor=0.3f;
void display()
{
	glLoadIdentity();
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();

	f32 dt = gt.Update();
	gluLookAt(c.position.x(), c.position.y(), c.position.z(),
		c.target.x(), c.target.y(), c.target.z(),
		c.up.x(), c.up.y(), c.up.z());
	
	setup_lights();

	// RED
	glPushMatrix();
	
	// Demonstating ways to rotate and translate
	
	// Matrix form
	//Mat44 translationMat = Mat44::BuildTranslationMatrix(0,0,-6);
	//Mat44 rotationMatrix = Mat44::BuildRotationMatrix(angle, float3(0,1,0));
	//Mat44 multTR = translationMat * rotationMatrix; // Does rotation then translation (local)
	//glMultMatrixf(multTR.Transpose().GetMatrix()); // REMEMBER TO TRANSPOSE THE MATRIX FOR OPENGL
	
	// With OpenGL functions
	//glTranslatef(0,0,-6);
	//glRotatef(angle, 0,1,0);
	
	// Quaternion interpolation
	glTranslatef(0,0,-6); Quaternion q;
	q = originTeapotRotation.lerp(finalTeapotRotation, teapotRotationInterpolationFactor);
	q = originTeapotRotation.slerp(finalTeapotRotation, teapotRotationInterpolationFactor);
	teapotRotationInterpolationFactor += dt * mfactor;
	if(teapotRotationInterpolationFactor>1 || teapotRotationInterpolationFactor<0) mfactor=-mfactor;
	glMultMatrixf(q.ToMat44().Transpose().GetMatrix());

	// Quaternions
	//glTranslatef(0,0,-6);
	//Quaternion q(float3(0,1,0), DEGTORAD(angle)); q.normalize();
	//glMultMatrixf(q.ToMat44().Transpose().GetMatrix());

	glutSolidTeapot(1.25);
	glPopMatrix();

	// GREEN
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, GREEN.GetVec());
	glTranslatef(0,0,6);
	//glRotatef(angle, 0,1,0);
	glutSolidTeapot(1.25);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(0,0,-15);
	glScalef(2,2,2);
	cube();
	glPopMatrix();


	TwRefreshBar(mainBar);
	TwDraw();

	glPopMatrix();

	angle += 25 * dt;
	ltangle += 0.1f * dt;
	glutSwapBuffers();
}
void idle()
{
	glutPostRedisplay();
}

void reshape (i32 width, i32 height)
{
	glViewport(0,0,(GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (width/height), 0.01, 100);
	glMatrixMode(GL_MODELVIEW);

	TwWindowSize(width,height);
}

void rotatecam(const f32 angle, const float3 &axis)
{
	Quaternion temp(axis.normalize(), DEGTORAD(angle));
	Quaternion qview(c.target.normalize());
	Quaternion qup(c.up.normalize());

	Quaternion res = temp * qview * temp.conjugate();
	c.target = res.tofloat3().normalize();

	float3 right = c.target ^ c.up;
	//c.up = c.target ^ right;

	//c.up = (temp * qup * temp.conjugate()).tofloat3().normalize();
};

void mouseFunction(i32 mouseX, i32 mouseY)
{
	if(!TwEventMouseMotionGLUT(mouseX, mouseY)) { }

	const int midx = glutGet(GLUT_WINDOW_WIDTH)/2, midy = glutGet(GLUT_WINDOW_HEIGHT)/2;
	if(mouseX == midx && mouseY == midy) return;
	glutWarpPointer(midx, midy);

	float2 sensitivity(15,15);

	// get change in x and y
	float2 mouseDelta(
		(midx - mouseX)/sensitivity.x(),
		(midy - mouseY)/sensitivity.y());
	mouseDelta *= gt.GetDeltaTime();
	//std::cout << mouseDelta.x() << " " << mouseDelta.y() << std::endl;

	//c.up.set(0,1,0);

	float3 axis = c.target - c.position;
	axis = axis ^ c.up;
	axis = axis.normalize();

	rotatecam(mouseDelta.x(), c.up);
	rotatecam(mouseDelta.y(), axis);
};

void OnMouseMotion(i32 mouseX, i32 mouseY)  // your callback function called by GLUT when mouse has moved
{
	if(!TwEventMouseMotionGLUT(mouseX, mouseY)) { }
}
void OnMouseButton(i32 glutButton, i32 glutState, i32 mouseX, i32 mouseY)
{
	if(!TwEventMouseButtonGLUT(glutButton, glutState, mouseX, mouseY)) { }
}
void OnSpecialEvent(i32 glutKey, i32 mouseX, i32 mouseY)
{
	if(!TwEventSpecialGLUT(glutKey,mouseX,mouseY)) { }
}

int main(i32 argc, c8 **argv)
{
	float3 dir(0,1,-1);
	float3 wUp(0,1,0);
	float3 lUp = wUp - (wUp.dot(dir)) * dir;


	originTeapotRotation = Quaternion(float3(0,1,0), DEGTORAD(0));
	finalTeapotRotation = Quaternion(float3(0,1,0), DEGTORAD(190));

	Camera c;
	c.speed = 10;
	c.position.set(0.0f);
	c.target.set(0,0,1);
	c.up.set(0,1,0);

	EngineConfig conf;
	conf.ParseConfigFile("Data/config.xml");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(conf.GetResolution().x, conf.GetResolution().y);
	glutCreateWindow("Scratch");
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION); // from freeglut, allows continued execution on window close

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyb);
	glutPassiveMotionFunc(mouseFunction);
	glutMotionFunc(OnMouseMotion);
	glutMouseFunc(OnMouseButton);
	glutSpecialFunc(OnSpecialEvent);

	setup_anttweakbar();
	TwGLUTModifiersFunc(glutGetModifiers);

	glEnable(GL_DEPTH_TEST);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glClearColor(0,0,0,1);

	gt.Init();
	gt.Update();

	glutMainLoop();

	return 0;
};

void TW_CALL SetTeapotInterpolationFactor(const void *value, void *clientData)
{
	f32 v = *(const f32*)value; v /= 100;
	if(v<0) v=0;
	if(v>1) v=1;
	*(f32*)clientData = v;
}
void TW_CALL GetTeapotInterpolationFactor(void *value, void *clientData)
{ 
	if(clientData){}
	*(f32 *)value = teapotRotationInterpolationFactor;
}

void setup_anttweakbar()
{
	TwInit(TW_OPENGL, NULL);
	TwWindowSize(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	mainBar = TwNewBar("Main");
	TwAddVarCB(mainBar, "Teapot Interpolation Factor", TW_TYPE_FLOAT, SetTeapotInterpolationFactor, GetTeapotInterpolationFactor, &teapotRotationInterpolationFactor, 0);
};

void setup_lights()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
		f32 xpos = sin(ltangle) * 5;
	f32 zpos = cos(ltangle) * 5;

	f32 ltPos[] = { xpos , 1, zpos, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, ltPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, BLACK.GetVec());
	glLightfv(GL_LIGHT0, GL_DIFFUSE, WHITE.GetVec());
	glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE.GetVec());

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, BLACK.GetVec());
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, RED.GetVec());
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, BLACK.GetVec());
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128.0f);
};

void cube()
{
		glBegin(GL_QUADS);		// Draw The Cube Using quads
    glColor3f(0.0f,1.0f,0.0f);	// Color Blue
    glVertex3f( 1.0f, 1.0f,-1.0f);	// Top Right Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f,-1.0f);	// Top Left Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f, 1.0f);	// Bottom Left Of The Quad (Top)
    glVertex3f( 1.0f, 1.0f, 1.0f);	// Bottom Right Of The Quad (Top)
    glColor3f(1.0f,0.5f,0.0f);	// Color Orange
    glVertex3f( 1.0f,-1.0f, 1.0f);	// Top Right Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f, 1.0f);	// Top Left Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f,-1.0f);	// Bottom Left Of The Quad (Bottom)
    glVertex3f( 1.0f,-1.0f,-1.0f);	// Bottom Right Of The Quad (Bottom)
    glColor3f(1.0f,0.0f,0.0f);	// Color Red	
    glVertex3f( 1.0f, 1.0f, 1.0f);	// Top Right Of The Quad (Front)
    glVertex3f(-1.0f, 1.0f, 1.0f);	// Top Left Of The Quad (Front)
    glVertex3f(-1.0f,-1.0f, 1.0f);	// Bottom Left Of The Quad (Front)
    glVertex3f( 1.0f,-1.0f, 1.0f);	// Bottom Right Of The Quad (Front)
    glColor3f(1.0f,1.0f,0.0f);	// Color Yellow
    glVertex3f( 1.0f,-1.0f,-1.0f);	// Top Right Of The Quad (Back)
    glVertex3f(-1.0f,-1.0f,-1.0f);	// Top Left Of The Quad (Back)
    glVertex3f(-1.0f, 1.0f,-1.0f);	// Bottom Left Of The Quad (Back)
    glVertex3f( 1.0f, 1.0f,-1.0f);	// Bottom Right Of The Quad (Back)
    glColor3f(0.0f,0.0f,1.0f);	// Color Blue
    glVertex3f(-1.0f, 1.0f, 1.0f);	// Top Right Of The Quad (Left)
    glVertex3f(-1.0f, 1.0f,-1.0f);	// Top Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f,-1.0f);	// Bottom Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f, 1.0f);	// Bottom Right Of The Quad (Left)
    glColor3f(1.0f,0.0f,1.0f);	// Color Violet
    glVertex3f( 1.0f, 1.0f,-1.0f);	// Top Right Of The Quad (Right)
    glVertex3f( 1.0f, 1.0f, 1.0f);	// Top Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f, 1.0f);	// Bottom Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f,-1.0f);	// Bottom Right Of The Quad (Right)
  glEnd();			// End Drawing The Cube
};

	/*
	
	void *gGlobalMemoryBuffer = 0;
#ifdef _DEBUG
//const u32 MAGIC_MEM_CLEAR = 0xEFBEADDE; // deadbeef on x86
const u32 MAGIC_MEM_CLEAR = 0xDEADBEEF;

inline void _dbg_fill_mem(void *mem, const u32 sz)
{
	printf("Debug mode\n");

	u32 *p = (u32*)mem;
	for(u32 i=0;i<sz/sizeof(u32);++i)
	{
		p[i] = MAGIC_MEM_CLEAR;
	}
};
inline void _dbg_check_mem(void* const mem, const u32 sz) // check for 0xDEADBEEF
{
	for(u32 i=0;i<sz/sizeof(u32);++i)
	{
		const u32 * const mval = &((u32*)mem)[i];
		assert(*mval == 0xDEADBEEF);
	}
	printf("_dbg_check_mem(%p, %d): Memory all OK\n", mem, sz);
};
#else
#define _dbg_fill_mem(mem,sz)
#define _dbg_check_mem(mem,sz)
#endif
	
	EngineConfig conf;
	conf.ParseConfigFile("Data/config.xml");

	const u32 SizeToAllocateInMB = 512; // Maximum memory application should be able to use
	const u32 AllocSize = (SizeToAllocateInMB * 1024) * 1024;

	PerfTimer pt;

	pt.start();
	gGlobalMemoryBuffer = malloc(AllocSize);
	pt.end();
	printf("Allocation time: %f\n", pt.time());

	pt.start();
	_dbg_fill_mem(gGlobalMemoryBuffer, AllocSize);
	pt.end();
	printf("Fill Memory time: %f\n", pt.time());

	pt.start();
	_dbg_check_mem(gGlobalMemoryBuffer, AllocSize);
	pt.end();
	printf("Memory check time: %f\n", pt.time());

	pt.start();
	free(gGlobalMemoryBuffer);
	pt.end();
	printf("Free time: %f\n", pt.time());

	getchar();
	return 0;*/
