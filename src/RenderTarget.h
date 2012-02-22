#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/GL.h>
#include <vector>
using namespace std;

struct FBOTexture
{
public:
	GLuint texID;
	unsigned int width, height;
	GLint internal_format;
	GLenum format;
	GLenum type;
	GLenum attachPoint;
};

class RenderTarget
{
private:
	GLuint fbo_id; // frame buffer object id
	unsigned int width, height; // width and height of textures

	vector<FBOTexture> textures;
public:
	RenderTarget()
	{
		width = 800;
		height = 600;
		glGenFramebuffers(1, &fbo_id);
	};

	RenderTarget(unsigned int pwidth, unsigned int pheight)
	{
		width = pwidth;
		height = pheight;
		glGenFramebuffers(1, &fbo_id);
	};

	void SetWidth(unsigned int w) { width = w; RecreateTextures(); }
	void SetHeight(unsigned int h) { height = h; RecreateTextures(); }
	void SetWidthAndHeight(unsigned int w, unsigned int h)
	{
		width = w;
		height = h;
		RecreateTextures();
	};

	void RecreateTextures()
	{
		for(unsigned int i=0;i<textures.size();++i)
		{
			FBOTexture &tex = textures[i];
			tex.width = width; tex.height = height;

			glBindTexture(GL_TEXTURE_2D, tex.texID);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexImage2D(GL_TEXTURE_2D, 0, tex.internal_format, tex.width, tex.height, 0, tex.format, tex.type, 0);

			Bind();
			glFramebufferTexture2D(GL_FRAMEBUFFER, tex.attachPoint , GL_TEXTURE_2D, tex.texID, 0);
			Unbind();
		}
		Unbind();
	};

	FBOTexture CreateDepthTexture()
	{
		return CreateAndAttachTexture(GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT, GL_DEPTH_ATTACHMENT);
	};

	// note: for depth textures, there is only ever 1 attachment point (GL_DEPTH_ATTACHMENT), hence why CreateDepthTexture() takes no arguments
	// in contrast, there can be many color attachments, from GL_COLOR_ATTACHMENT0+0 to GL_COLOR_ATTACHMENT0+GL_MAX_COLOR_ATTACHMENTS-1
	FBOTexture CreateColorTexture(GLenum attachmentPoint)
	{
		return CreateAndAttachTexture(GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, attachmentPoint);
	};

	FBOTexture CreateAndAttachTexture(GLint internal_format, GLenum format, GLenum type, GLenum attachmentPoint)
	{
		FBOTexture tex;
		glGenTextures(1, &tex.texID);
		
		tex.width = width; tex.height = height;
		tex.internal_format = internal_format;
		tex.format = format;
		tex.type = type;
		tex.attachPoint = attachmentPoint;

		glBindTexture(GL_TEXTURE_2D, tex.texID);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, tex.internal_format, tex.width, tex.height, 0, tex.format, tex.type, 0);

		Bind();
		glFramebufferTexture2D(GL_FRAMEBUFFER, tex.attachPoint , GL_TEXTURE_2D, tex.texID, 0);
		Unbind();

		glBindTexture(GL_TEXTURE_2D, 0);

		textures.push_back(tex);
		return textures.back();
	};

	void Bind()
	{
		glBindTexture(GL_TEXTURE_2D,0);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);
	};

	void Bind(GLenum target)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(target, fbo_id);
	}

	static void Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
};