#include "TextureManager.h"
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

	Texture t;
	if(t.Load(_filename))
	{
		textures[filename_hash] = t;
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