#pragma once

#include "..\Shader\ShaderProgram.h"
#include "..\Texture\Texture.h"

class SimpleLightingShaderProgram : public ShaderProgram
{
public:
	SimpleLightingShaderProgram(GLuint shaderProgramID);
	~SimpleLightingShaderProgram();

	virtual void loadUniformLocations();
	virtual void fillUniformLocation(MeshNode* node, std::vector<LightNode*> lights, bool drawOcclusion = false);
	virtual void fillUniformLocation(LightShaft* lightShaft, LightNode* light);

private:
	GLuint locationMVP;
	GLuint locationV;
	GLuint locationM;
	GLuint locationTexture;
	GLuint locationLight;
	GLuint locationOcclusion;
	GLuint locationClipPlane;
	
	void useLights(std::vector<LightNode*> lights);
	void bindTextures(MeshNode* node);
};

