#pragma once

#include "ctypes.h"
#include <iosfwd>

#include "Mat44.h"
#include "float2.h"
#include "float3.h"
#include "float4.h"
#include "Texture.h"
#include "ShaderObject.h"

class Shader : public Resource
{
private:
	GLuint shaderProgramID;
	
	VertexShaderHandle vs;
	FragmentShaderHandle fs;

	void Unload();
	bool HasLinked();

public:
	Shader() : shaderProgramID(0), vs(0), fs(0) {};
	~Shader() { Unload(); };

	//bool CreateProgram(VertexShaderObject* vs_handle, FragmentShaderObject* fs_handle);
	bool CreateProgram(VertexShaderHandle vs_handle, FragmentShaderHandle fs_handle);

	void Activate();
	void Deactivate();

	const GLint GetUniformLocation(const GLchar* name);

	void SetUniform(const c8 * const name, const GLint val);
	void SetUniform(const c8 * const name, const Texture &tex);
	void SetUniform(const c8 * const name, const f32 val);
	void SetUniform(const c8 * const name, const float2 &val);
	void SetUniform(const c8 * const name, const float3 &val);
	void SetUniform(const c8 * const name, const float4 &val);
	void SetUniform(const c8 * const name, const Mat44 &val);
	
	void PrintProgramLog(std::ostream &out);
	void PrintActiveUniforms(std::ostream &out);
};