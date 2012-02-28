#include "Mesh.h"

const GLvoid* BUFFER_OFFSET(const u32 i)
{
	return ((c8 *)NULL + (i));
};

void Mesh::Unload()
{
	if(meshvbo.meshData) { glDeleteBuffers(1, &meshvbo.meshData); }
	if(meshvbo.indexData) { glDeleteBuffers(1, &meshvbo.indexData); }
	meshvbo.meshData = meshvbo.indexData = dbg_vertex_array_sz = dbg_index_array_sz = 0;
};

bool Mesh::BuildVBO(const VERTEX *vertexData, const u32 vertexArraySz, const u32 *indexData, const u32 indexArraySz)
{
	// Unload first to avoid memory leaks
	this->Unload();
	if(!vertexData || !vertexArraySz || !indexData || !indexArraySz) { return false; }

	// Create buffers
	glGenBuffers(1, &meshvbo.meshData);
	glGenBuffers(1, &meshvbo.indexData);
	if(!meshvbo.meshData || !meshvbo.indexData) { Unload(); return false; }

	// Bind buffers and send data
	glBindBuffer(GL_ARRAY_BUFFER, meshvbo.meshData);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VERTEX) * vertexArraySz, vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshvbo.indexData);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * indexArraySz, indexData, GL_STATIC_DRAW);

	dbg_vertex_array_sz = vertexArraySz;
	dbg_index_array_sz = indexArraySz;

	// Unbind buffers (do not want to leave them enabled when we quit, want to leave a clean environment)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return true;
}

void Mesh::Draw() const
{
	glPolygonMode(GL_FRONT_AND_BACK, polygonFillMode);

	glBindBuffer(GL_ARRAY_BUFFER, meshvbo.meshData);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshvbo.indexData);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(VERTEX), BUFFER_OFFSET(VERTEX_POSITION_BUFFER_OFFSET));
	glNormalPointer(GL_FLOAT, sizeof(VERTEX), BUFFER_OFFSET(VERTEX_NORMAL_BUFFER_OFFSET));
	glTexCoordPointer(2, GL_FLOAT, sizeof(VERTEX), BUFFER_OFFSET(VERTEX_UV_BUFFER_OFFSET));

	glDrawElements(geometryDataFormat, dbg_index_array_sz, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
};