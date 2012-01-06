#pragma once

#include "ShaderObject.h"
#include <assert.h>

// Encapsulates the collection of the shaders (vert+frag) and program object
class ShaderSet
{
	GLint shaderProgramID;
	bool linked;

	// keep pointers to the vertex and fragment shaders from which the program
	// may be created (note: the data within cannot be modified)
	const ShaderObject * vertexShader;
	const ShaderObject * fragmentShader;

	// can create the program object manually 
	// if we want. otherwise just call CreateProgram() and it will do it for you
	inline bool Init();
	inline bool CreateProgram(const ShaderObject *vertShader, ShaderObject *fragShader);
	void Cleanup(); // deletes the program, sets linked to false, and nulls the vert+frag ShaderObject pointers

	GLint GetShaderProgramID() const { return shaderProgramID; }
	const ShaderObject* GetVertexShader() const { return vertexShader; }
	const ShaderObject* GetFragmentShader() const { return fragmentShader; }

	ShaderSet() : shaderProgramID(-1), linked(false), vertexShader(0), fragmentShader(0) {};
};
