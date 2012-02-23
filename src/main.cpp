#ifdef _WIN32
#pragma warning (disable : 4505) // used to disable warning from glut code, "unreferenced local function has been removed"
#endif

#include "RenderTarget.h"
#include "EngineConfig.h"
#include "testobjects.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "PerfTimer.h"
#include "GameTime.h"
#include "Quaternion.h"
#include "AntTweakBarFunctions.h"
#include <AntTweakBar.h>

GameTime gt;
Camera c;
TwBar *mainBar;
bool mouseRotateCamera = true; // set to false to disable mouse tracking (allowing mouse to be placed anywhere in window)
Quaternion originTeapotRotation, finalTeapotRotation;
RenderTarget *ptarg;
int windowWidth, windowHeight;
f32 angle=0, ltangle=0;
bool fboactive=false;
Texture *test_texture;
TextureManager texMan;
ShaderManager shaderMan;
u32 basicTexturingShaderID; Shader *basicTexturingShader;
GLenum fboBuff[] = { GL_COLOR_ATTACHMENT0 };
GLenum windowBuff[] = { GL_BACK };
FBOTexture colorTex;

void standard_render_nofbo()
{
	glClearColor(0,0,0,0);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0f);

	glDisable(GL_CULL_FACE);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT); // < required for the glutSolidTeapot() as its faces are the wrong order

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	float3 ntarg = c.position + c.target.normalize(); ntarg.normalize();
	gluLookAt(c.position.x(), c.position.y(), c.position.z(),
		ntarg.x(), ntarg.y(), ntarg.z(),
		c.up.x(), c.up.y(), c.up.z());

	glPushMatrix();

	test_texture->Activate();
	basicTexturingShader->Activate();

	glPushMatrix();
	glScaled(0.1,0.1,0.1);
	glTranslatef(0,0,-2.5);
	draw_cube();
	glPopMatrix();

	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glTranslated(0,-0.1,0);
	glScaled(0.05,0.05,0.05);
	glColor3f(0,1,0);
	draw_floor_plane();
	glPopMatrix();

	basicTexturingShader->Deactivate();
	test_texture->Deactivate();

	glPopMatrix();

	TwRefreshBar(mainBar);
	TwDraw();

	angle += 0.03f;
	glutSwapBuffers();
};

void render_thru_fbo()
{
	glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, 0);

	// Bind FBO
	ptarg->Bind();

	// setup draw buffers/viewport etc
	glDrawBuffers(1, fboBuff); // only required if rendering to >1 buffer
	glViewport(0,0,colorTex.width, colorTex.height);
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	gluPerspective(45, windowWidth/windowHeight,0.3,200);
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();

	// setup camera
	float3 ntarg = c.position + c.target.normalize(); ntarg.normalize();
	gluLookAt(c.position.x(), c.position.y(), c.position.z(), ntarg.x(), ntarg.y(),
		ntarg.z(), c.up.x(), c.up.y(), c.up.z());

	// Draw stuff . . .
	glPushMatrix();
	glTranslatef(-1,0,-6);
	glColor3f(1,0,0);
	glRotatef(angle, 0,1,0);
	test_texture->Activate();
	glCullFace(GL_FRONT);
	glutSolidTeapot(1);
	glCullFace(GL_BACK);
	test_texture->Deactivate();
	glPopMatrix();

	// Unbind FBO
	ptarg->Unbind();

	// set viewport, clear colors etc
	glDrawBuffers(1, windowBuff);
	glViewport(0,0,windowWidth,windowHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// draw fullscreen quad with renderbuffer (test)
	glEnable(GL_TEXTURE_2D); glBindTexture(GL_TEXTURE_2D, colorTex.texID);
	draw_fullscreen_quad();
	glBindTexture(GL_TEXTURE_2D, 0);

	TwRefreshBar(mainBar);
	TwDraw();

	angle += 0.06f;
	glutSwapBuffers();
};

void display()
{
	gt.Update();
	if(fboactive) render_thru_fbo();
	else standard_render_nofbo();
}

void keyb(uc8 vkey, i32 x, i32 y)
{
	switch(tolower(vkey))
	{
	case 27: glutLeaveMainLoop(); break; // escape key

	case 'f': fboactive = !fboactive; break;

	case 'w': c.position += c.target * (f32)gt.GetDeltaTime(); break;
	case 's': c.position -= c.target * (f32)gt.GetDeltaTime(); break;
	case 'a': c.position -= c.target.cross(c.up) * (f32)gt.GetDeltaTime(); break;
	case 'd': c.position += c.target.cross(c.up) * (f32)gt.GetDeltaTime(); break;
	case 'q': c.position += c.up * (f32)gt.GetDeltaTime(); break;
	case 'e': c.position -= c.up * (f32)gt.GetDeltaTime(); break;
	
	case 'r':
		{
			mouseRotateCamera = !mouseRotateCamera;
			glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH)/2, glutGet(GLUT_WINDOW_HEIGHT)/2);
		} break;
	};
};

void idle()
{
	gt.Update();
	c.position.set(1.33f, 1.23f, 1.32f);
	c.target.set(-0.54f, -0.45f, -0.66f);
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
	f32 mouseDiffX = ((f32)MX - (f32)mouseX) * rotationSpeedX * (f32)gt.GetDeltaTime();
	f32 mouseDiffY = ((f32)MY - (f32)mouseY) * rotationSpeedY * (f32)gt.GetDeltaTime();

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

void Load(EngineConfig &conf)
{
	float3 dir(0,1,-1), wUp(0,1,0);
	float3 lUp = wUp - wUp.dot(dir) * dir;

	originTeapotRotation = Quaternion(float3(0,1,0), DEGTORAD(0));
	finalTeapotRotation = Quaternion(float3(0,1,0), DEGTORAD(190));

	ptarg = new RenderTarget(windowWidth, windowHeight);
	ptarg->CreateDepthTexture();
	colorTex = ptarg->CreateColorTexture(GL_COLOR_ATTACHMENT0);

	test_texture = texMan.LoadTextureFromFile("Data/test.jpg");

	if(shaderMan.LoadShader(basicTexturingShaderID, "Data/Shaders/WriteDepth.vert", "Data/Shaders/WriteDepth.frag"))
	{
		basicTexturingShader = shaderMan.GetShader(basicTexturingShaderID);
		basicTexturingShader->SetUniform("baseMap", *test_texture);
	}

	glutWarpPointer(windowWidth/2, windowHeight/2); // make sure to do this before initialising the camera below (otherwise, the camera will immediately be placed somewhere random)

	Camera c;
	c.speed = 10;
	c.position.set(1.33f, 1.23f, 1.32f);
	c.target.set(-0.54f, -0.45f, -0.66f);

	gt.Update();
};

int main(i32 argc, c8 **argv)
{
	EngineConfig conf; conf.ParseConfigFile("Data/config.xml");
	windowWidth = conf.GetResolution().x; windowHeight = conf.GetResolution().y;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ALPHA);
	glutInitWindowSize(windowWidth, windowHeight);
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

	setup_anttweakbar(mainBar);
	TwGLUTModifiersFunc(glutGetModifiers);

	glewInit();

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glClearColor(0,0,0,1);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	Load(conf);

	glutMainLoop();

	return 0;
};