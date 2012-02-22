#pragma once

#include "ctypes.h"
#include <iosfwd>

#include "Mat44.h"
#include "float2.h"
#include "float3.h"
#include "float4.h"
#include "Texture.h"

enum ShaderError
{
	ERROR_FAIL=false, // generic failure
	ERROR_OK=true, // success

	// failed to create vertex shader,
	// fragment shader, or both
	ERROR_INVALID_VS_ID,
	ERROR_INVALID_FS_ID,
	ERROR_INVALID_VS_FS_ID,

	ERROR_VS_COMPILE_FAILED,
	ERROR_FS_COMPILE_FAILED,

	ERROR_CREATE_PROGRAM_FAILED,
	ERROR_LINK_FAILED,
};

// Usage process:
// * Initialise with Init()
// * CompileVertexShader(...) and CompileFragmentShader(...)
// * CreateProgram()
// * SetUniform(...) if neccessary
// * Activate() to use shader
// * Deactivate() after use
class Shader
{
private:
	bool isActive; // deactivates entire shader
	GLuint vertexShaderID, fragmentShaderID, shaderProgramID;
	u32 error; // error flag (used for more details if function returns ERROR_FAIL)
public:
	Shader();
	~Shader();

	const u32 GetLastError() const;

	const bool Valid() const; // returns true if vertexShaderID, fragmentShaderID and shaderProgramID != 0

	void SetActive(bool active);
	const bool IsActive() const;

	const bool Init();

	// calls Init() so you dont have to
	const bool LoadShader(const c8* fragment_shader_filename, const c8* vertex_shader_filename);

	bool CompileVertexShader(const c8 * const src);
	bool CompileFragmentShader(const c8 * const src);

	bool CreateProgram(); // creates and links shader program

	const GLint GetUnformLocation(const GLchar* name); // 0 on fail or -1

	void SetUniform(const GLint _id, const GLint val);
	void SetUniform(const c8 * const name, const Texture &tex);
	void SetUniform(const c8 * const name, const f32 val);
	void SetUniform(const c8 * const name, const GLint val);
	void SetUniform(const c8 * const name, const float2 &val);
	void SetUniform(const c8 * const name, const float3 &val);
	void SetUniform(const c8 * const name, const float4 &val);
	void SetUniform(const c8 * const name, const Mat44 &val);

	void Activate();
	void Deactivate();
	
	void PrintShaderLog(GLenum shaderType, std::ostream &out);
	void PrintProgramLog(std::ostream &out);
	void PrintActiveUniforms(std::ostream &out);
};