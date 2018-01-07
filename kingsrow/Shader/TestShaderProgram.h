#pragma once

#include "..\Shader\ShaderProgram.h"
#include "..\Texture\Texture.h"

class TestShaderProgram : public ShaderProgram
{
public:
	TestShaderProgram(GLuint shaderProgramID);
	~TestShaderProgram();

	virtual void loadUniformLocations();
	virtual void fillUniformLocation(MeshNode* node, std::vector<LightNode*> lights, bool drawOcclusion = false);
	virtual void fillUniformLocation(LightShaft* lightShaft, LightNode* light);

private:
	GLuint locationLightScreenPos;
	GLuint locationTex;
	GLuint locationSamples;
	GLuint locationExposure;
	GLuint locationDecay;
	GLuint locationDensity;
	GLuint locationWeight;
};

