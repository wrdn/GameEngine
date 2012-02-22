#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
};

ShaderManager::~ShaderManager()
{
	try
	{
		Clean();
	}
	catch(...) { }
};

u32 ShaderManager::AddShader()
{
	shaders.push_back(new Shader());
	handles.push_back(ShaderHandle(shaders.back()));
	return handles.size()-1;
};

bool ShaderManager::RemoveShader(u32 index)
{
	if(index < handles.size())
	{
		delete handles[index].shader;
		handles[index].shader = 0;
		return true;
	}
	return false;
};

Shader * const ShaderManager::GetShader(u32 index) const
{
	if(index < handles.size())
	{
		return handles[index].shader;
	}
	return 0;
};

void ShaderManager::Clean()
{
	for(u32 i=0;i<handles.size();++i)
	{
		delete handles[i].shader;
	}
	handles.clear();
	shaders.clear();
};