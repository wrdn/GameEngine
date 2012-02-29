#ifdef _WIN32
#pragma warning (disable : 4505) // used to disable warning from glut code, "unreferenced local function has been removed"
#endif

#include <GL/glew.h>

#include "RenderTarget.h"
#include "ResourceManager.h"
#include "ShaderManager.h"
#include "EngineConfig.h"
#include "Quaternion.h"
#include "GameTime.h"
#include "testobjects.h"

#include "AntTweakBarFunctions.h"
#include <AntTweakBar.h>

GameTime gt;
Camera c;
TwBar *mainBar;
bool mouseRotateCamera = true; // set to false to disable mouse tracking (allowing mouse to be placed anywhere in window)
Quaternion originTeapotRotation, finalTeapotRotation;

RenderTargetHandle basic_shadow_mapping_buffer; // http://fabiensanglard.net/shadowmapping/index.php
RenderTargetHandle pcf_shadow_buffer; // http://fabiensanglard.net/shadowmappingPCF/index.php
RenderTargetHandle vsm_shadow_buffer, vsm_blur_buffer; // http://fabiensanglard.net/shadowmappingVSM/index.php
RenderTargetHandle activeBuffer;

// BASIC SHADOW MAPPING
u32 shadowMappingShaderID; Shader *shadowMappingShader;
FBOTexture colorTex, depthTex;

// PCF SHADOW MAPPING
u32 pcfShadowMappingShaderID; Shader *pcfShadowMappingShader;
FBOTexture pcfDepthTex;

// VSM SHADOW MAPPING
u32 vsmShadowMappingShaderID, vsmStoreMomentsShaderID, vsmBlurShaderID;
Shader *vsmShadowMappingShader, *vsmStoreMomentsShader, *vsmBlurShader;
FBOTexture vsmDepthTex, vsmColorTex, vsmBlurColorTex;

int windowWidth, windowHeight;
f32 angle=0, ltangle=0;
bool fboactive=false;
ShaderManager shaderMan;

TextureHandle test_tex_handle;

GLenum fboBuff[] = { GL_COLOR_ATTACHMENT0 };
GLenum windowBuff[] = { GL_BACK };

const float NEAR_PLANE = 3;
const float FAR_PLANE = 200;

f32 radius = 20;
f32 anglet=0;

void DrawFullScreenQuad(u32 texID)
{
	glDisable(GL_CULL_FACE);
	glActiveTextureARB(GL_TEXTURE0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (double)windowWidth/(double)windowHeight, NEAR_PLANE, FAR_PLANE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// set viewport, clear colors etc
	glDrawBuffers(1, windowBuff);
	glViewport(0,0,windowWidth,windowHeight);

	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	// draw fullscreen quad with renderbuffer (test)
	glEnable(GL_TEXTURE_2D);
	glActiveTextureARB(GL_TEXTURE0);
	glLoadIdentity();
	glBindTexture(GL_TEXTURE_2D, texID);
	draw_fullscreen_quad();
	glBindTexture(GL_TEXTURE_2D, 0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
};

void setup_matrices(f32 posx, f32 posy, f32 posz, f32 lookx, f32 looky, f32 lookz)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (double)windowWidth/(double)windowHeight, NEAR_PLANE,FAR_PLANE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(posx, posy, posz, lookx, looky, lookz, 0,1,0);
};

void setTextureMatrix(void)
{
	static double modelView[16];
	static double projection[16];
	
	const GLdouble bias[16] = {	
		0.5, 0.0, 0.0, 0.0, 
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
	0.5, 0.5, 0.5, 1.0};
	
	glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	
	
	glMatrixMode(GL_TEXTURE);
	glActiveTextureARB(GL_TEXTURE7);
	
	glLoadIdentity();	
	glLoadMatrixd(bias);
	
	glMultMatrixd (projection);
	glMultMatrixd (modelView);
	
	glMatrixMode(GL_MODELVIEW);
}

#pragma warning (disable : 4702)

void vsm_shadow_mapping_render()
{
	glUseProgram(0);
	vsm_shadow_buffer->Bind();

	glEnable(GL_DEPTH_TEST); glEnable(GL_CULL_FACE);
	glViewport(0,0, vsm_shadow_buffer->GetWidth(), vsm_shadow_buffer->GetHeight());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set up light view
	f32 lightX = radius * cos(anglet), lightZ = radius * sin(anglet);
	setup_matrices(lightX,6,lightZ,0,0,0);
	anglet += 0.5f * (f32)gt.GetDeltaTime();

	// render from light pov
	vsmStoreMomentsShader->Activate();
	glDisable(GL_CULL_FACE); draw_floor_plane(); 
	//glEnable(GL_CULL_FACE); glCullFace(GL_FRONT);
	draw_cube();
	vsmStoreMomentsShader->Deactivate();

	glGenerateMipmap(GL_TEXTURE_2D);
	setTextureMatrix();

	// **** BLUR SHADOW MAP HERE ... ***

	RenderTarget::Unbind(); // we have now rendered depth and depth^2 into VSM FBO and blurred the result

	glViewport(0,0,windowWidth,windowHeight); // RENDERING TO WINDOW
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//DrawFullScreenQuad(vsmColorTex.texID);
	//return;

	vsmShadowMappingShader->SetUniform("shadowMap", 7);

	vsmShadowMappingShader->Activate();

	glActiveTextureARB(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D,vsmColorTex.texID);

	glLoadIdentity();
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	gluPerspective(45, (double)windowWidth/(double)windowHeight,NEAR_PLANE, FAR_PLANE);
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	float3 ntarg = c.position + c.target.normalize(); ntarg.normalize();
	gluLookAt(c.position.x(), c.position.y(), c.position.z(),
		ntarg.x(), ntarg.y(), ntarg.z(),
		c.up.x(), c.up.y(), c.up.z());
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glColor3f(1,0,0); draw_floor_plane();
	glColor3f(0,1,0); draw_cube();

	vsmShadowMappingShader->Deactivate();

};

void pcf_shadow_mapping_render()
{
	pcf_shadow_buffer->Bind();
	glUseProgram(0);

	glEnable(GL_DEPTH_TEST); glEnable(GL_CULL_FACE);
	glViewport(0,0, pcf_shadow_buffer->GetWidth(), pcf_shadow_buffer->GetHeight()); // RENDER TO SIZE OF FBO
	glClear(GL_DEPTH_BUFFER_BIT); // CLEAR DEPTH
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); // only write to z buffer

	// view from light
	f32 lightX = radius * cos(anglet), lightZ = radius * sin(anglet);
	setup_matrices(lightX,6,lightZ,0,0,0);
	anglet += 0.5f * (f32)gt.GetDeltaTime();

	// render objects from light pov
	glEnable(GL_CULL_FACE); glCullFace(GL_FRONT); // DRAW OBJECTS WITH CULL FRONT ENABLED
	draw_floor_plane(); draw_cube();

	setTextureMatrix();
	RenderTarget::Unbind();
	
	glViewport(0,0,windowWidth,windowHeight); // RENDERING TO WINDOW
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); // RENABLE COLORING
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// RENDER SCENE FROM CAMERA WITH SHADOWS
	pcfShadowMappingShader->SetUniform("ShadowMap", 7);
	f32 xoffset = 1.0f / pcf_shadow_buffer->GetWidth();
	xoffset = 1.0f / windowWidth;
	f32 yoffset = 1.0f / pcf_shadow_buffer->GetHeight();
	yoffset = 1.0f / windowHeight;
	pcfShadowMappingShader->SetUniform("xPixelOffset", xoffset);
	pcfShadowMappingShader->SetUniform("yPixelOffset", yoffset);

	glActiveTextureARB(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D,pcfDepthTex.texID);

	pcfShadowMappingShader->Activate();
	
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	gluPerspective(45, (double)windowWidth/(double)windowHeight,NEAR_PLANE, FAR_PLANE);
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	float3 ntarg = c.position + c.target.normalize(); ntarg.normalize();
	gluLookAt(c.position.x(), c.position.y(), c.position.z(),
		ntarg.x(), ntarg.y(), ntarg.z(),
		c.up.x(), c.up.y(), c.up.z());
	glCullFace(GL_BACK);
	glColor3f(1,0,0); draw_floor_plane();
	glColor3f(0,1,0); draw_cube();

	pcfShadowMappingShader->Deactivate();
};

void basic_shadow_mapping_render()
{
	basic_shadow_mapping_buffer->Bind(); // BIND FBO
	glUseProgram(0); // DEACTIVATE ANY SHADERS

	glEnable(GL_DEPTH_TEST); glEnable(GL_CULL_FACE);

	glViewport(0,0, basic_shadow_mapping_buffer->GetWidth(), basic_shadow_mapping_buffer->GetHeight()); // RENDER TO SIZE OF FBO
	glClear(GL_DEPTH_BUFFER_BIT); // CLEAR DEPTH
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	f32 lightX = radius * cos(anglet);
	f32 lightZ = radius * sin(anglet);
	setup_matrices(lightX,6,lightZ,0,0,0); // VIEW FROM LIGHT
	//setup_matrices(-2,12,-10,0,0,0); // VIEW FROM LIGHT
	anglet += 0.5f * (f32)gt.GetDeltaTime();

	glEnable(GL_CULL_FACE); glCullFace(GL_FRONT); // DRAW OBJECTS WITH CULL FRONT ENABLED
	draw_floor_plane();
	draw_cube();

	setTextureMatrix(); // PUTS MODELVIEWPROJECTION MATRIX INTO GLTEXTURE7 + BIAS

	RenderTarget::Unbind(); // UNBIND FBO

	glViewport(0,0,windowWidth,windowHeight); // RENDERING TO WINDOW
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); // RENABLE COLORING
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//glDisable(GL_DEPTH_TEST);
	//DrawFullScreenQuad(depthTex.texID);
	//return;

	shadowMappingShader->SetUniform("ShadowMap", 7); // ENABLE SHADOW MAPPING SHADER
	glActiveTextureARB(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D,depthTex.texID);
	shadowMappingShader->Activate();

	// SETUP CAMERA
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	gluPerspective(45, (double)windowWidth/(double)windowHeight,NEAR_PLANE, FAR_PLANE);
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	float3 ntarg = c.position + c.target.normalize(); ntarg.normalize();
	gluLookAt(c.position.x(), c.position.y(), c.position.z(),
		ntarg.x(), ntarg.y(), ntarg.z(),
		c.up.x(), c.up.y(), c.up.z());

	glCullFace(GL_BACK); // DRAW OBJECTS WITH SHADOWS
	glColor3f(1,0,0);
	draw_floor_plane();
	glColor3f(0,1,0);
	draw_cube();

	shadowMappingShader->Deactivate(); // DISABLE SHADOW MAPPING SHADER
}

void display()
{
	gt.Update();
	
	basic_shadow_mapping_render();
	//pcf_shadow_mapping_render();
	//vsm_shadow_mapping_render();

	//DrawFullScreenQuad(test_tex_handle->GetGLTextureID());

	glutSwapBuffers();

	//if(fboactive) render_thru_fbo();
	//else standard_render_nofbo();
}

int currentshadowmapsizeindex=0;
const vec2i shadowMapSizes[] = 
{
	vec2i(128,128),
	vec2i(256,256),
	vec2i(512,512),
	vec2i(1024,1024),
	vec2i(2048,2048),
	vec2i(4096,4096),
	vec2i(8192,8192),
};
int numSizes = sizeof(shadowMapSizes) / sizeof(vec2i);

void keyb(uc8 vkey, i32 x, i32 y)
{
	switch(tolower(vkey))
	{
	case 27: glutLeaveMainLoop(); break; // escape key

	case 'f': fboactive = !fboactive; break;

	case 'w': c.position += c.target * c.speed * (f32)gt.GetDeltaTime(); break;
	case 's': c.position -= c.target * c.speed * (f32)gt.GetDeltaTime(); break;
	case 'a': c.position -= c.target.cross(c.up) * c.speed * (f32)gt.GetDeltaTime(); break;
	case 'd': c.position += c.target.cross(c.up) * c.speed * (f32)gt.GetDeltaTime(); break;
	case 'q': c.position += c.up * c.speed * (f32)gt.GetDeltaTime(); break;
	case 'e': c.position -= c.up * c.speed * (f32)gt.GetDeltaTime(); break;
	
	case 'n':
		{
			++currentshadowmapsizeindex;
			if(currentshadowmapsizeindex == numSizes)
			{
				currentshadowmapsizeindex = 0;
			}
			
			activeBuffer->SetWidthAndHeight(shadowMapSizes[currentshadowmapsizeindex].x, shadowMapSizes[currentshadowmapsizeindex].y);
			cout << "Shadow map size: " << shadowMapSizes[currentshadowmapsizeindex].x << " " << shadowMapSizes[currentshadowmapsizeindex].y << endl;
			break;
		}

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
	glutPostRedisplay();
}

void reshape (i32 width, i32 height)
{
	windowWidth = width;
	windowHeight = height;

	glViewport(0,0,windowWidth, windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (double)windowWidth/(double)windowHeight, NEAR_PLANE,FAR_PLANE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//basic_shadow_mapping_buffer->SetWidthAndHeight(width, height);

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

void LoadPCF(EngineConfig &conf)
{
	//pcf_shadow_buffer = new RenderTarget(1024,1024);
	pcf_shadow_buffer = ResourceManager::get().CreateAndGetResource<RenderTarget>();
	pcf_shadow_buffer->SetWidthAndHeight(1024,1024);
	pcf_shadow_buffer->SetDrawReadBufferState(GL_NONE, GL_NONE);
	pcfDepthTex = pcf_shadow_buffer->CreateAndAttachTexture(
		GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE,
		GL_DEPTH_ATTACHMENT, false, GL_NEAREST, GL_NEAREST,
		GL_CLAMP, GL_CLAMP);

	shaderMan.LoadShader(pcfShadowMappingShaderID, "Data/Shaders/PCF_ShadowMapping.vert",
		"Data/Shaders/PCF_ShadowMapping.frag");
	pcfShadowMappingShader = shaderMan.GetShader(pcfShadowMappingShaderID);
	if(pcfShadowMappingShader)
	{
		pcfShadowMappingShader->SetUniform("ShadowMap", 7);
		f32 xoffset = 1.0f / pcf_shadow_buffer->GetWidth();
		f32 yoffset = 1.0f / pcf_shadow_buffer->GetHeight();
		pcfShadowMappingShader->SetUniform("xPixelOffset", xoffset);
		pcfShadowMappingShader->SetUniform("yPixelOffset", yoffset);
	}
};

void LoadVSM(EngineConfig &conf)
{
	// VSM shadow FBO
	vsm_shadow_buffer = ResourceManager::get().CreateAndGetResource<RenderTarget>();
	vsm_shadow_buffer->SetWidthAndHeight(1024,1024);
	vsmDepthTex = vsm_shadow_buffer->CreateAndAttachTexture(GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE,
		GL_DEPTH_ATTACHMENT, false, GL_NEAREST, GL_NEAREST, GL_CLAMP, GL_CLAMP);
	vsmColorTex = vsm_shadow_buffer->CreateAndAttachTexture(GL_RGB32F, GL_RGB, GL_FLOAT, GL_COLOR_ATTACHMENT0, true,
		GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, GL_CLAMP);

	// Blur FBO
	vsm_blur_buffer = ResourceManager::get().CreateAndGetResource<RenderTarget>();
	vsm_blur_buffer->SetWidthAndHeight(1024,1024);
	vsmBlurColorTex = vsm_blur_buffer->CreateAndAttachTexture(GL_RGB32F, GL_RGB, GL_FLOAT, GL_COLOR_ATTACHMENT0, false,
		GL_LINEAR, GL_LINEAR, GL_CLAMP, GL_CLAMP);

	// Shaders
	shaderMan.LoadShader(vsmStoreMomentsShaderID, "Data/Shaders/VSM/VSM_StoreMoments.vert", "Data/Shaders/VSM/VSM_StoreMoments.frag");
	vsmStoreMomentsShader = shaderMan.GetShader(vsmStoreMomentsShaderID);

	shaderMan.LoadShader(vsmShadowMappingShaderID, "Data/Shaders/VSM/VSM.vert", "Data/Shaders/VSM/VSM.frag");
	vsmShadowMappingShader = shaderMan.GetShader(vsmShadowMappingShaderID);
	if(vsmShadowMappingShader)
	{
		vsmShadowMappingShader->SetUniform("shadowMap", 7);
	}
};

void LoadBasicShadowMapping(EngineConfig &conf)
{
	basic_shadow_mapping_buffer = ResourceManager::get().CreateAndGetResource<RenderTarget>();
	basic_shadow_mapping_buffer->SetWidthAndHeight(1024,1024);

	basic_shadow_mapping_buffer->SetDrawReadBufferState(GL_NONE, GL_NONE);
	depthTex = basic_shadow_mapping_buffer->CreateAndAttachTexture(
		GL_DEPTH_COMPONENT,
		GL_DEPTH_COMPONENT,
		GL_UNSIGNED_BYTE,
		GL_DEPTH_ATTACHMENT,
		false,
		GL_NEAREST, GL_NEAREST,
		GL_CLAMP, GL_CLAMP);

	shaderMan.LoadShader(shadowMappingShaderID, "Data/Shaders/ShadowMapping.vert", "Data/Shaders/ShadowMapping.frag");
	shadowMappingShader = shaderMan.GetShader(shadowMappingShaderID);
	shadowMappingShader->SetUniform("ShadowMap", 7);
};

void LoadCamera()
{
	glutWarpPointer(windowWidth/2, windowHeight/2); // make sure to do this before initialising the camera below (otherwise, the camera will immediately be placed somewhere random)

	c.speed = 10;
	c.position.set(-3,5,-8);
	c.target.set(0.25,-0.5,1);
};

void Load(EngineConfig &conf)
{
	originTeapotRotation = Quaternion(float3(0,1,0), DEGTORAD(0));
	finalTeapotRotation = Quaternion(float3(0,1,0), DEGTORAD(190));

	test_tex_handle = ResourceManager::get().CreateAndGetResource<Texture>("testjpeg");
	test_tex_handle->Load("Data/test.jpg");

	// returns the same data
	TextureHandle tex2 = ResourceManager::get().CreateAndGetResource<Texture>("testjpeg");

	/*shaderMan.LoadShader(vsmDepthWriteShaderID, "Data/Shaders/WriteDepth.vert", "Data/Shaders/WriteDepth.frag");
	vsmDepthWriterShader = shaderMan.GetShader(vsmDepthWriteShaderID);
	
	shaderMan.LoadShader(vsmShaderID, "Data/Shaders/VSM.vert", "Data/Shaders/VSM.frag");
	vsmShader = shaderMan.GetShader(vsmShaderID);
	vsmShader->SetUniform("shadowMap", 7);*/

	LoadBasicShadowMapping(conf);
	//LoadPCF(conf);
	//LoadVSM(conf);


	//activeBuffer = pcf_shadow_buffer;
	activeBuffer = basic_shadow_mapping_buffer;
	//activeBuffer = vsm_shadow_buffer;

	LoadCamera();
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

	ResourceManager::Cleanup();

	return 0;
};