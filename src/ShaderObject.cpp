#include "ShaderObject.h"
#include <iostream>

inline bool ShaderObject::Init(ShaderType _shaderType)
{
	if(!_shaderType || shaderID) return false;

	shaderType = _shaderType;
	shaderID = glCreateShader(shaderType);
	hasCompiled = false;
	return shaderID>=0;
};

inline GLint ShaderObject::CompileShader(const GLchar* src)
{
	if(!shaderID) return 0; // no shader object
	if(hasCompiled) return 1; // shader already compiled

	const i32 len = (i32)strlen(src);
	glShaderSource(shaderID, 1, (const GLchar**)&src, &len);
	glCompileShader(shaderID);

	GLint shaderCompileStatus;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderCompileStatus);
	hasCompiled = shaderCompileStatus == GL_TRUE;
	return hasCompiled;
};

// call this to reset the ShaderObject (it can then be repurposed if you so desire)
inline void ShaderObject::Cleanup()
{
	shaderType = GLInvalidShader;
	if(shaderID) { glDeleteShader(shaderID); shaderID = 0; }
	hasCompiled = false;
};

void ShaderObject::PrintShaderLog(std::ostream &out)
{
	if(!shaderID) return;

	// we only grab the first 4k of the log (should be more than enough).
	// and much better than allocating from the heap for a log
	// alternative if we really want to allocate memory is to use alloca() and
	// allocate off the stack
	c8 logBuffer[4096];

	i32 logLen=0;
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLen);
	logLen = logLen < 4096 ? logLen : 4096; // min(logLen, 4096)
	glGetShaderInfoLog(shaderID, logLen, 0, logBuffer);
	out << logBuffer << std::endl;
};