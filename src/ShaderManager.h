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

		VertexShaderObject *vso = new VertexShaderObject();
		FragmentShaderObject *fso = new FragmentShaderObject();

		vso->CompileFromFile(vertexShaderFilename);
		fso->CompileFromFile(fragmentShaderFilename);
		
		if( ! sh->CreateProgram(VertexShaderHandle(vso), FragmentShaderHandle(fso)))
		{
			std::cout << vertexShaderFilename << ", " << fragmentShaderFilename << std::endl;
			vso->PrintShaderLog(std::cout);
			fso->PrintShaderLog(std::cout);
			sh->PrintProgramLog(std::cout);

			RemoveShader(id);
			return false;
		}
		out_id = id;
		return true;
	};
};