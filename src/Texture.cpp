#include "Texture.h"
#include "stb_image.h"

void Texture::SetParameteri(GLenum param, u32 v) const
{
	Activate();
	glTexParameteri(GL_TEXTURE_2D, param, v);
	Deactivate();
};

void Texture::SetParameterf(GLenum param, f32 v) const
{
	Activate();
	glTexParameterf(GL_TEXTURE_2D, param, v);
	Deactivate();
};

bool Texture::Load(const char *filename)
{
	Unload();

	int x, y, n;
	unsigned char *pixdata = stbi_load(filename, &x, &y, &n, 0);
	if(!pixdata || n>4 || n<3) { return false; }

	glGenTextures(1, &textureID);
	if(textureID)
	{
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, magFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);

		int internalFormat = GL_RGBA8, format = GL_RGBA;
		if(n == 3) { internalFormat = GL_RGB8; format = GL_RGB; }
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, x, y, 0, format, GL_UNSIGNED_BYTE, pixdata); 
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
		stb_free(pixdata);

		width = x;
		height = y;

		return true;
	}
	return false;
};

void Texture::Unload()
{
	if(textureID)
	{
		glDeleteTextures(1, &textureID);
	}
	textureID = 0;
};

void Texture::Activate() const
{
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GetTextureSlot());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, magFilter);
	
	glBindTexture(GL_TEXTURE_2D, GetGLTextureID());
};

void Texture::Deactivate() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
};