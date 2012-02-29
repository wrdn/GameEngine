#include "GraphicsObject.h"
bool GraphicsObject::GLOBAL_USE_SHADERS = true;
bool GraphicsObject::GLOBAL_USE_TEXTURES = true;

void GraphicsObject::Draw()
{
	if(!mesh) return;

	// Activate shader
	if(GLOBAL_USE_SHADERS && local_use_shaders && objectMaterial.GetShader())
	{
		objectMaterial.GetShader()->Activate();
	};

	// Activate textures
	if(GLOBAL_USE_TEXTURES && local_use_textures)
	{
		for(u32 i=0;i<objectMaterial.GetTextures().size();++i)
		{
			TextureHandle t = objectMaterial.GetTextures()[i];
			glActiveTexture(t->GetTextureSlot());
			t->Activate();
		}
	}

	objectMaterial.Activate();

	glPushMatrix();

	// Transform model
	glTranslatef(position.x(), position.y(), position.z());
	glRotatef(orientation.x(), 1,0,0);
	glRotatef(orientation.y(), 0,1,0);
	glRotatef(orientation.z(), 0,0,1);
	glScalef(scale.x(), scale.y(), scale.z());

	// Draw model
	glColor3f(1,1,1); // this is used so even if OpenGL lighting disabled (or no shaders), the object will still appear
	glPolygonMode(GL_FRONT_AND_BACK, polygonFillMode);
	mesh->Draw();

	glPopMatrix();

	// Deactivate shader and textures
	glUseProgram(0);
	for(u32 i=0;i<objectMaterial.GetTextures().size();++i)
	{
		TextureHandle t = objectMaterial.GetTextures()[i];
		glActiveTexture(t->GetTextureSlot());
		t->Deactivate();
	}
	glActiveTexture(GL_TEXTURE0);
};