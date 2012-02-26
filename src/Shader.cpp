#include "Shader.h"
#include "strutils.h"
#include <iostream>

Shader::Shader() : isActive(true),
	vertexShaderID(0), fragmentShaderID(0), shaderProgramID(0),
	error(ERROR_OK)
{
};

Shader::~Shader()
{
	try
	{
		// TODO: Cleanup the OpenGL shader objects here
		glUseProgram(0);
		glDetachObjectARB(shaderProgramID, vertexShaderID);
		glDetachObjectARB(shaderProgramID, fragmentShaderID);
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		glDeleteProgram(shaderProgramID);

		// invalidate shader IDs
		vertexShaderID = fragmentShaderID = shaderProgramID = 0;
	}
	catch(...) { }
};

const u32 Shader::GetLastError() const
{
	return error;
};

void Shader::SetActive(bool active)
{
	isActive = active;
};

const bool Shader::IsActive() const
{
	return isActive;
};

const bool Shader::Init()
{
	// Delete old shaders if already created
	if(vertexShaderID)
	{
		glDeleteShader(vertexShaderID);
	}
	if(fragmentShaderID)
	{
		glDeleteShader(fragmentShaderID);
	}
	
	vertexShaderID = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	if(!vertexShaderID)
	{
		error = ERROR_INVALID_VS_ID;
		return ERROR_FAIL;
	}

	fragmentShaderID = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	if(!fragmentShaderID)
	{
		if(vertexShaderID)
			glDeleteShader(vertexShaderID);

		error = ERROR_INVALID_FS_ID;
		return ERROR_FAIL;
	}

	return ERROR_OK;
};

const bool Shader::LoadShader(const c8* fragment_shader_filename, const c8* vertex_shader_filename)
{
	if(!vertexShaderID || !fragmentShaderID)
	{
		if(!Init()) { return false; }
	}

	c8* frag_src = read_src_fast(fragment_shader_filename);
	c8* vert_src = read_src_fast(vertex_shader_filename);

	if(!CompileVertexShader(vert_src) || !CompileFragmentShader(frag_src))
	{
		delete [] frag_src;
		delete [] vert_src;
		return false;
	}
	delete [] frag_src;
	delete [] vert_src;

	return CreateProgram();
};

bool Shader::CompileVertexShader(const c8 * const src)
{
	// Error checking
	if(!fragmentShaderID && !vertexShaderID)
	{ error = ERROR_INVALID_VS_FS_ID; return ERROR_FAIL; }
	else if(!fragmentShaderID)
	{ error =  ERROR_INVALID_FS_ID; return ERROR_FAIL; }
	else if(!vertexShaderID)
	{ error = ERROR_INVALID_VS_ID; return ERROR_FAIL; }

	GLint len = strlen(src);

	glShaderSourceARB(vertexShaderID, 1, (const GLchar**)&src, &len);
	glCompileShaderARB(vertexShaderID);

	i32 shader_ok = 0;
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &shader_ok);
	if(!shader_ok)
	{
		error = ERROR_VS_COMPILE_FAILED;
		return ERROR_FAIL;
	}

	return ERROR_OK;
};

bool Shader::CompileFragmentShader(const c8 * const src)
{
	// Error checking
	if(!fragmentShaderID && !vertexShaderID)
	{ error = ERROR_INVALID_VS_FS_ID; return ERROR_FAIL; }
	else if(!fragmentShaderID)
	{ error =  ERROR_INVALID_FS_ID; return ERROR_FAIL; }
	else if(!vertexShaderID)
	{ error = ERROR_INVALID_VS_ID; return ERROR_FAIL; }

	GLint len = strlen(src);
	glShaderSourceARB(fragmentShaderID, 1, (const GLchar**)&src, &len);
	glCompileShader(fragmentShaderID);

	i32 shader_ok = 0;
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &shader_ok);
	if(!shader_ok)
	{
		error = ERROR_FS_COMPILE_FAILED;
		return ERROR_FAIL;
	}

	return ERROR_OK;
};

bool Shader::CreateProgram()
{
	if(!fragmentShaderID && !vertexShaderID)
	{ error = ERROR_INVALID_VS_FS_ID; return ERROR_FAIL; }
	else if(!fragmentShaderID)
	{ error =  ERROR_INVALID_FS_ID; return ERROR_FAIL; }
	else if(!vertexShaderID)
	{ error = ERROR_INVALID_VS_ID; return ERROR_FAIL; }

	shaderProgramID = glCreateProgram();
	if(!shaderProgramID) { error = ERROR_CREATE_PROGRAM_FAILED; return ERROR_FAIL; };

	glAttachObjectARB(shaderProgramID, vertexShaderID);
	glAttachObjectARB(shaderProgramID, fragmentShaderID);
	glLinkProgramARB(shaderProgramID);

	i32 link_status;
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &link_status);
	if(!link_status)
	{
		error = ERROR_LINK_FAILED;
		return ERROR_FAIL;
	}

	return ERROR_OK;
};

const GLint Shader::GetUnformLocation(const GLchar* name)
{
	return glGetUniformLocationARB(shaderProgramID, name);
};

void Shader::SetUniform(const GLint _id, const GLint val)
{
	i32 cp=0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &cp); // get current shader (activated again after setting uniform)

	Activate();
	glUniform1i(_id, val);
	
	glUseProgram(cp);
};


void Shader::SetUniform(const c8 * const name, const Texture &tex)
{
	SetUniform(GetUnformLocation(name), tex.GetTextureSlotIndex());
};

void Shader::SetUniform(const c8 * const name, const f32 val)
{
	i32 cp=0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &cp); // get current shader (activated again after setting uniform)

	Activate();
	GLint _id = GetUnformLocation(name);
	glUniform1f(_id, val);
	
	glUseProgram(cp);
};

void Shader::SetUniform(const c8 * const name, const GLint val)
{
	i32 cp=0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &cp); // get current shader (activated again after setting uniform)

	Activate();
	GLint _id = GetUnformLocation(name);
	glUniform1i(_id, val);
	
	glUseProgram(cp);
};

void Shader::SetUniform(const c8 * const name, const float2 &val)
{
	i32 cp=0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &cp); // get current shader (activated again after setting uniform)

	Activate();
	GLint _id = GetUnformLocation(name);
	glUniform2fv(_id, 1, val.GetVec());
	
	glUseProgram(cp);
};

void Shader::SetUniform(const c8 * const name, const float3 &val)
{
	i32 cp=0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &cp); // get current shader (activated again after setting uniform)

	Activate();
	GLint _id = GetUnformLocation(name);
	glUniform3fv(_id, 1, val.GetVec());
	
	glUseProgram(cp);
};

void Shader::SetUniform(const c8 * const name, const float4 &val)
{
	i32 cp=0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &cp); // get current shader (activated again after setting uniform)

	Activate();
	GLint _id = GetUnformLocation(name);
	glUniform4fv(_id, 1, val.GetVec());
	
	glUseProgram(cp);
};

void Shader::SetUniform(const c8 * const name, const Mat44 &val)
{
	i32 cp=0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &cp); // get current shader (activated again after setting uniform)

	Activate();
	GLint _id = GetUnformLocation(name);
	glUniformMatrix4fv(_id, 1, GL_FALSE, val.GetMatrix());

	glUseProgram(cp);
};

void Shader::Activate()
{
	glUseProgram(shaderProgramID);
};

void Shader::Deactivate()
{
	glUseProgram(0);
};

void Shader::PrintShaderLog(GLenum shaderType, std::ostream &out)
{
	u32 shaderID=0;
	if(shaderType == GL_VERTEX_SHADER)
		shaderID = vertexShaderID;
	else if(shaderType == GL_FRAGMENT_SHADER)
		shaderID = fragmentShaderID;
	else return;

	i32 logLength;
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
	c8* _log = new c8[logLength];
	glGetShaderInfoLog(shaderID, logLength, NULL, _log);
	out << _log << std::endl;
	delete [] _log;
};

void Shader::PrintProgramLog(std::ostream &out)
{
	GLint logLen=0;
	glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &logLen);
	c8 *log = new c8[logLen];
	glGetProgramInfoLog(shaderProgramID, logLen, NULL, log);
	out << log << std::endl;
	delete [] log;
};

void Shader::PrintActiveUniforms(std::ostream &out)
{
	i32 total = -1;
	glGetProgramiv( shaderProgramID, GL_ACTIVE_UNIFORMS, &total );
	if(total == 0) return;

	for(i32 i=0; i<total; ++i)  {
		i32 name_len=-1, num=-1;
		GLenum type = GL_ZERO;
		c8 name[100];
		glGetActiveUniform( shaderProgramID, GLuint(i), sizeof(name)-1,
			&name_len, &num, &type, name );
		name[name_len] = 0;
		out << name << ", ";
	};
	out << std::endl;
};

const bool Shader::Valid() const
{
	return (vertexShaderID && fragmentShaderID && shaderProgramID);
};