#pragma once

#include "color.h"
#include <vector>
#include "Texture.h"
#include "Shader.h"

class Material
{
private:
	color ka, kd, ks, ke;
	f32 shininess;

	std::vector<TextureHandle> textures;
	ShaderHandle activeShader;

public:
	Material() : ka(0.1f), kd(1.0f), ks(0.15f), ke(0.0f), shininess(10) {};

	color GetKA() const { return ka; };
	color GetKD() const { return kd; };
	color GetKS() const { return ks; };
	color GetKE() const { return ke; };
	f32 GetShininess() const { return shininess; };

	void SetKA(const color &col) { ka = col; };
	void SetKD(const color &col) { kd = col; };
	void SetKS(const color &col) { ks = col; };
	void SetKE(const color &col) { ke = col; };
	void SetShininess(const f32 shine) { shininess = shine; };
	
	std::vector<TextureHandle> &GetTextures() { return textures; };

	void ClearTextures() { textures.clear(); };

	int AddTexture(TextureHandle t)
	{
		textures.push_back(t);
		return textures.size()-1;
	};

	void SetShader(ShaderHandle active_shader)
	{
		activeShader = active_shader;
	};

	ShaderHandle GetShader() { return activeShader; };

	void Activate()
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ka.GetVec());
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, kd.GetVec());
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ks.GetVec());
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, ke.GetVec());
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	};
};