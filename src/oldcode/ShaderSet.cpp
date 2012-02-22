#include "ShaderSet.h"

inline bool ShaderSet::Init() // can create the program object manually if we want. otherwise just call CreateProgram() and it will do it for you
{
	if(shaderProgramID) return false; // already created the program

	shaderProgramID = glCreateProgram();
	return shaderProgramID > 0;
};

inline bool ShaderSet::CreateProgram(const ShaderObject *vertShader, ShaderObject *fragShader)
{
	if( (!vertShader || !fragShader) ||
		(!vertShader->GetShaderID() || !fragShader->GetShaderID()) ) { return false; }
	if(!shaderProgramID) { if(!Init()) { return false; } }

	// make sure we have a vertex and fragment shader
	assert(vertShader->GetShaderType() == GLVertexShader);
	assert(fragShader->GetShaderType() == GLFragmentShader);

	glAttachShader(shaderProgramID, vertShader->GetShaderID());
	glAttachShader(shaderProgramID, fragShader->GetShaderID());
	glLinkProgram(shaderProgramID);

	GLint link_status; glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &link_status);
	linked = link_status == GL_TRUE;
	
	return linked;
}

void ShaderSet::Cleanup()
{
	if(shaderProgramID)
	{
		glDeleteProgram(shaderProgramID);
	}
	shaderProgramID = 0;
	linked = false;
	vertexShader = fragmentShader = 0;
};