#pragma once

#include <GL/glew.h>

#include "ctypes.h"
#include <string>

enum ShaderType
{
	GLInvalidShader=0,
	GLVertexShader = GL_VERTEX_SHADER,
	GLFragmentShader = GL_FRAGMENT_SHADER,
};

// The only difference between a vertex shader and fragment shader is the
// parameter passed to glCreateProgram(...) - all other code is identical
// Therefore there is only a single class to represent a shader, ShaderObject.
// Simply pass VertexShader or FragmentShader to Init() to set the class up.
class ShaderObject
{
private:
	ShaderType shaderType;
	GLint shaderID;
	bool hasCompiled;

public:
	inline bool Init(ShaderType _shaderType);

	inline GLint CompileShader(const GLchar* src);

	// call this to reset the ShaderObject (it can then be repurposed if you so desire)
	inline void Cleanup();

	void PrintShaderLog(std::ostream &out);

	ShaderType GetShaderType() const { return shaderType; }
	GLint GetShaderID() const { return shaderID; }
	bool ShaderCompiled() const { return hasCompiled; }

	ShaderObject() : shaderType(GLInvalidShader), shaderID(-1), hasCompiled(false) {};
};
