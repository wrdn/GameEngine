#pragma warning (disable : 4505) // used to disable warning from glut code

#include <iostream>
#include <stdio.h>
#include <assert.h>

#include "util.h"
#include "PerfTimer.h"
#include "EngineConfig.h"
#include "GameTime.h"

#include <GL/freeglut.h>

void *gGlobalMemoryBuffer = 0;

i32 add(const i32 a, const i32  b)
{
	return a+b;
};

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


GameTime gt;
Camera c;

void keyb(uc8 _key, i32 x, i32 y)
{
	if(x||y){}

	uc8 key = (uc8)tolower(_key);
	if(key == 'w')
	{
		//std::cout << gt.GetDeltaTime() << std::endl;
		//c.position.z(c.position.z() + (2 * gt.GetDeltaTime()));

		c.position += c.target * 15 * gt.GetDeltaTime();
	}
	else if(key == 'a')
	{
		c.position -= c.target * 15 * gt.GetDeltaTime();
	}
	else if(key == 's')
	{
	}
	else if(key == 'd')
	{
	}
	glutPostRedisplay();
};

f32 angle=0, ltangle=0;
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

	glPushMatrix();
	glTranslatef(0,0,-6);
	glRotatef(angle, 0,1,0);
	glutSolidTeapot(1.25);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, GREEN.GetVec());
	glTranslatef(0,0,6);
	glRotatef(angle, 0,1,0);
	glutSolidTeapot(1.25);
	glPopMatrix();

	glPopMatrix();

	angle += 15 * dt;
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
}

int main(i32 argc, c8 **argv)
{
	if(argc){} if(argv){}

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

	glEnable(GL_DEPTH_TEST);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glClearColor(0,0,0,1);

	gt.Init();
	gt.Update();

	glutMainLoop();

	return 0;

	/*EngineConfig conf;
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
};
