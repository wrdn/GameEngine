#pragma once

#include "Shader.h"
#include <vector>

class ShaderManager
{
private:
	struct ShaderHandle
	{
	public:
		Shader *shader;

		ShaderHandle() : shader(0) { };
		explicit ShaderHandle(Shader *sh) : shader(sh) { };
	};

	std::vector<Shader*> shaders;
	std::vector<ShaderHandle> handles;

public:
	ShaderManager();
	~ShaderManager();

	u32 AddShader();
	bool RemoveShader(u32 index);
	Shader * const GetShader(u32 index) const;

	void Clean();

	bool LoadShader(u32 &out_id, const c8* vertexShaderFilename, const c8* fragmentShaderFilename)
	{
		u32 id = AddShader();
		Shader *sh = GetShader(id);

		if(!sh->LoadShader(fragmentShaderFilename, vertexShaderFilename))
		{
			std::cout << vertexShaderFilename << ", " << fragmentShaderFilename << std::endl;
			sh->PrintShaderLog(GL_VERTEX_SHADER, std::cout);
			sh->PrintShaderLog(GL_FRAGMENT_SHADER, std::cout);
			sh->PrintProgramLog(std::cout);
			
			RemoveShader(id);

			return false;
		}

		out_id = id;
		return true;
	};
};