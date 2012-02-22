#ifdef _WIN32
#pragma warning (disable : 4505) // used to disable warning from glut code
#pragma warning (disable : 4702) // used to disable warning from glut code
#endif

#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <cmath>

#include "util.h"
#include "PerfTimer.h"
#include "EngineConfig.h"
#include "GameTime.h"

#include "RenderTarget.h"

#include <GL/freeglut.h>
#include <AntTweakBar.h>

#include "Quaternion.h"

#include "TextureManager.h"
#include "ShaderManager.h"

void keyb(uc8 vkey, i32 x, i32 y);
void display();
void idle();
void reshape (i32 width, i32 height);
void mouseFunction(i32 mouseX, i32 mouseY);
void OnMouseMotion(i32 mouseX, i32 mouseY);
void OnMouseButton(i32 glutButton, i32 glutState, i32 mouseX, i32 mouseY);
void OnSpecialEvent(i32 glutKey, i32 mouseX, i32 mouseY);
int main(i32 argc, c8 **argv);
void TW_CALL SetTeapotInterpolationFactor(const void *value, void *clientData);
void TW_CALL GetTeapotInterpolationFactor(void *value, void *clientData);
void setup_anttweakbar();
void setup_lights();
void cube();

GameTime gt;
Camera c;
TwBar *mainBar;
f32 teapotRotationInterpolationFactor=0; bool automaticTeapotRotation=true;
bool mouseRotateCamera = true; // set to false to disable mouse tracking (allowing mouse to be placed anywhere in window)

Quaternion originTeapotRotation;
Quaternion finalTeapotRotation;

RenderTarget *ptarg;
int windowWidth, windowHeight;
bool fboactive=false;

Texture *test_texture;
TextureManager texMan;

ShaderManager shaderMan;

u32 basicTexturingShaderID; Shader *basicTexturingShader;

void keyb(uc8 vkey, i32 x, i32 y)
{
	if(x||y){} uc8 key = (uc8)tolower(vkey);
	if(key == 27) { glutLeaveMainLoop(); return; } // escape key

	else if(key == 'f') { fboactive = !fboactive; return; }

	else if(key == 'r')
	{
		mouseRotateCamera = !mouseRotateCamera;
		const i32 midx = glutGet(GLUT_WINDOW_WIDTH)/2, midy = glutGet(GLUT_WINDOW_HEIGHT)/2;
		glutWarpPointer(midx, midy);
		return;
	}
	else if(key == 'w') // move cam 'forwards'
	{
		c.position += c.target * 15 * gt.GetDeltaTime();
	}
	else if(key == 's') // move cam 'backwards'
	{
		c.position -= c.target * 15 * gt.GetDeltaTime();
	}
	else if(key == 'a')
	{
		float3 right = c.target.cross(c.up);
		c.position -= right * 15 * gt.GetDeltaTime();
	}
	else if(key == 'd')
	{
		float3 right = c.target.cross(c.up);
		c.position += right * 15 * gt.GetDeltaTime();
	}
	else if(key == 'q')
	{
		c.position += c.up * 15 * gt.GetDeltaTime();
	}
	else if(key == 'e')
	{
		c.position -= c.up * 15 * gt.GetDeltaTime();
	}
};

f32 angle=0, ltangle=0;
f32 mfactor=0.3f;

void standard_render_nofbo()
{
	glClearColor(0,0,0,0);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0f);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix();

	test_texture->Activate();
	basicTexturingShader->Activate();

	glPushMatrix();
	glTranslatef(0,0,-6);
	glRotatef(angle,0,1,0);
	glColor3f(1,0,0);
	glutSolidTeapot(1.0f);
	glPopMatrix();


	basicTexturingShader->Deactivate();

	glPopMatrix();
	
	angle += 0.03f;
	glutSwapBuffers();
};

GLenum fboBuff[] = { GL_COLOR_ATTACHMENT0 };
GLenum windowBuff[] = { GL_BACK_LEFT };

FBOTexture colorTex;

void render_thru_fbo()
{
	glClearDepth(1.0f);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	ptarg->Bind();
	glDrawBuffers(1, fboBuff);

	glViewport(0,0,colorTex.width, colorTex.height);

	glClearColor(0,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, windowWidth/windowHeight,0.3,200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(-1,0,-6);
	glColor3f(1,0,0);
	glRotatef(angle, 0,1,0);
	test_texture->Activate();
	glutSolidTeapot(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1,0,-6);
	glColor3f(1,1,0);
	glRotatef(angle, 0,1,0);
	glutSolidTeapot(1);
	test_texture->Deactivate();
	glPopMatrix();

	ptarg->Unbind();

	glDisable(GL_CULL_FACE);

	glDrawBuffers(1, windowBuff);

	glViewport(0,0,windowWidth,windowHeight);

	glClearColor(1,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, colorTex.texID);

	glMatrixMode (GL_MODELVIEW);
	glPushMatrix ();
	glLoadIdentity ();
	glMatrixMode (GL_PROJECTION);
	glPushMatrix ();
	glLoadIdentity ();
	glBegin (GL_QUADS);
	glTexCoord2f(0,0); glVertex3i (-1, -1, -1);
	glTexCoord2f(1,0); glVertex3i (1, -1, -1);
	glTexCoord2f(1,1); glVertex3i (1, 1, -1);
	glTexCoord2f(0,1); glVertex3i (-1, 1, -1);
	glEnd ();
	glPopMatrix ();
	glMatrixMode (GL_MODELVIEW);
	glPopMatrix ();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	angle += 0.03f;
	glutSwapBuffers();
};

void display()
{
	/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glLoadIdentity();

	test_texture->Activate();
	basicTexturingShader->Activate();

	glPushMatrix();
	glTranslatef(0,0,-6);
	glRotatef(angle,0,1,0);
	glColor3f(1,1,0);
	glutSolidTeapot(1.0f);
	glPopMatrix();

	angle += 0.06f;
	glutSwapBuffers();
	return;*/

	if(!fboactive)
	{
		standard_render_nofbo();
		return;
	}
	render_thru_fbo();
	return;

	glLoadIdentity();
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();

	f32 dt = gt.Update();
	/*gluLookAt(c.position.x(), c.position.y(), c.position.z(),
		c.target.x(), c.target.y(), c.target.z(),
		c.up.x(), c.up.y(), c.up.z());*/
	float3 ntarg = c.position + c.target.normalize(); ntarg.normalize();
	gluLookAt(c.position.x(), c.position.y(), c.position.z(),
		ntarg.x(), ntarg.y(), ntarg.z(),
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
	if(automaticTeapotRotation) { teapotRotationInterpolationFactor += dt * mfactor; }
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
	//glTranslatef(0,0,-15);
	glScalef(10,10,10);
	//cube();
	glPopMatrix();

	glPushMatrix();
	glScalef(5,5,5);
	glTranslatef(0,-1,0);
	glBegin(GL_QUADS);
	glVertex3f(-1,0,-1);
	glVertex3f(1,0,-1);
	glVertex3f(1,0,1);
	glVertex3f(-1,0,1);
	glEnd();
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
	windowWidth = width;
	windowHeight = height;

	glViewport(0,0,windowWidth, windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, windowWidth/windowHeight, 0.5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	ptarg->SetWidthAndHeight(width, height);

	TwWindowSize(width,height);
}

void mouseFunction(i32 mouseX, i32 mouseY)
{
	TwEventMouseMotionGLUT(mouseX, mouseY);
	if(!mouseRotateCamera) return;

	const i32 MX = glutGet(GLUT_WINDOW_WIDTH)/2;
	const i32 MY = glutGet(GLUT_WINDOW_HEIGHT)/2;
	if(MX == mouseX && MY == mouseY) return;

	const f32 rotationSpeedX = 10, rotationSpeedY = 15;
	f32 mouseDiffX = ((f32)MX - (f32)mouseX) * rotationSpeedX * gt.GetDeltaTime();
	f32 mouseDiffY = ((f32)MY - (f32)mouseY) * rotationSpeedY * gt.GetDeltaTime();

	static f32 AccumPitchDegs = 0;
	AccumPitchDegs += mouseDiffY;
	if(AccumPitchDegs > 90.0f)
	{
		mouseDiffY = 90.0f - (AccumPitchDegs - mouseDiffY);
		AccumPitchDegs = 90.0f;
	}
	else if(AccumPitchDegs < -90.0f)
	{
		mouseDiffY = -90.0f - (AccumPitchDegs - mouseDiffY);
		AccumPitchDegs = -90.0f;
	}

	// Rotation around world y axis
	float3 WORLD_UP(0,1,0);
	Quaternion tempx(WORLD_UP, DEGTORAD(mouseDiffX)); // rotation around world up vector (0,1,0)
	c.target = (tempx * c.target * tempx.conjugate()).tofloat3(); // same as calling tempx.rotate(c.target)

	// Rotation around world x axis
	float3 WORLD_RIGHT = c.target.cross(c.up);
	Quaternion tempy(WORLD_RIGHT, DEGTORAD(mouseDiffY));
	Quaternion targQuat(c.target);
	c.target = (targQuat * tempy).tofloat3();

	glutWarpPointer(MX, MY);
};

void OnMouseMotion(i32 mouseX, i32 mouseY)  // your callback function called by GLUT when mouse has moved
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ALPHA);
	glutInitWindowSize(conf.GetResolution().x, conf.GetResolution().y);
	windowWidth = conf.GetResolution().x; windowHeight = conf.GetResolution().y;
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
	//glutSetCursor(GLUT_CURSOR_NONE);

	setup_anttweakbar();
	TwGLUTModifiersFunc(glutGetModifiers);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glClearColor(0,0,0,1);

	glewInit();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	ptarg = new RenderTarget(windowWidth, windowHeight);
	ptarg->CreateDepthTexture();
	colorTex = ptarg->CreateColorTexture();
	
	test_texture = texMan.LoadTextureFromFile("Data/test.jpg");

	if(shaderMan.LoadShader(basicTexturingShaderID, "Data/Shaders/BasicTexturing.vert", "Data/Shaders/BasicTexturing.frag"))
	{
		basicTexturingShader = shaderMan.GetShader(basicTexturingShaderID);
		basicTexturingShader->SetUniform("baseMap", *test_texture);
	}
	
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
	TwAddVarRW(mainBar, "Teapot Automatic Rotation", TW_TYPE_BOOL32, &automaticTeapotRotation, 0);
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
