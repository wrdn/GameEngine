#pragma once

#include "ctypes.h"
#include <GL/glew.h>

enum OpenGLTextureSlot
{
	SLOT_GL_TEXTURE_0 = GL_TEXTURE0,
	SLOT_GL_TEXTURE_1 = GL_TEXTURE1,
	SLOT_GL_TEXTURE_2 = GL_TEXTURE2,
	SLOT_GL_TEXTURE_3 = GL_TEXTURE3,
	SLOT_GL_TEXTURE_4 = GL_TEXTURE4,
	SLOT_GL_TEXTURE_5 = GL_TEXTURE5,
	SLOT_GL_TEXTURE_6 = GL_TEXTURE6,
	SLOT_GL_TEXTURE_7 = GL_TEXTURE7,
};

// Used to manage textures from OpenGL.
class Texture
{
private:
	u32 id;
	u32 minFilter, magFilter, wrapS, wrapT; // automatically set on activation
	u32 width, height;
	OpenGLTextureSlot textureSlot; // GL_TEXTURE_0 to GL_TEXTURE_7, slots are at GL_TEXTURE_0+n
public:
	Texture(void);
	explicit Texture(const u32 _id);
	~Texture(void);

	const u32 GetID() const;
	void SetID(const u32 _id);

	void Activate() const;
	void Deactivate() const;

	// http://www.opengl.org/sdk/docs/man/xhtml/glTexParameter.xml
	void SetMinFilter(const u32 _minFilter);
	void SetMagFilter(const u32 _magFilter);
	void SetWrapS(const u32 wrapMode);
	void SetWrapT(const u32 wrapMode);

	const u32 GetMinFilter() const;
	const u32 GetMagFilter() const;
	const u32 GetWrapS() const;
	const u32 GetWrapT() const;

	void SetParameteri(u32 param, u32 v) const;

	void SetWidth(const u32 _width);
	void SetHeight(const u32 _height);
	const u32 GetWidth() const;
	const u32 GetHeight() const;

	void SetTextureSlot(OpenGLTextureSlot s) { textureSlot = s; };

	const OpenGLTextureSlot GetTextureSlot() const { return textureSlot; };

	// returns a value in range 0 to 7 (used by shader system)
	const u32 GetTextureSlotIndex() const { return textureSlot - SLOT_GL_TEXTURE_0; };
};