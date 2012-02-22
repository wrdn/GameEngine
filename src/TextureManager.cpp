#include "TextureManager.h"
#include "stb_image.h"
#include "util.h"
#include <GL\GLU.h>

TextureManager::TextureManager(void)
{
}

TextureManager::~TextureManager(void)
{
	try
	{
		Cleanup();
	}
	catch(...) { };
}

void TextureManager::Cleanup()
{
	// Generally the texture manager will be a singleton, and will exist throughout the entire application
	// The texture manager will ensure that any textures are cleaned up (if not done elsewhere)
	for (std::map<u32,Texture>::iterator it=textures.begin() ; it != textures.end(); it++ )
	{
		glDeleteTextures(1, &it->first);
	}
	textures.clear(); 
};

Texture* TextureManager::LoadTextureFromFile(const c8* const _filename)
{
	unsigned long filename_hash = hash_djb2((const uc8*)_filename);
	if(Texture *t = GetTexture(filename_hash)) { return t; };

	int x, y, n;
	unsigned char *pixdata = stbi_load(_filename, &x, &y, &n, 0);
	if(!pixdata || n>4 || n<3) { return 0; }

	u32 id; glGenTextures(1, &id);
	if(id)
	{
		glBindTexture(GL_TEXTURE_2D, id);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		
		int internalFormat = GL_RGBA8, format = GL_RGBA;
		if(n == 3) { internalFormat = GL_RGB8; format = GL_RGB; }

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, x, y, 0, format, GL_UNSIGNED_BYTE, pixdata); 
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		stb_free(pixdata);

		Texture tex(id);
		textures[filename_hash] = tex;
		return &textures[filename_hash];
	}
	return 0;
};

Texture* TextureManager::GetTexture(const u32 filename_hash)
{
	if(textures.count(filename_hash) > 0)
	{
		return &textures.at(filename_hash);
	}
	return NULL;
};

bool TextureManager::DeleteTexture(const u32 _id)
{
	if(textures.count(_id) > 0)
	{
		glDeleteTextures(1, &_id);
		textures.erase(_id);
		return true;
	}
	return false;
};