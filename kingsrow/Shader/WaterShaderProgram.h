#pragma once

#include "..\Shader\ShaderProgram.h"
#include "..\Texture\Texture.h"

class WaterShaderProgram : public ShaderProgram
{
public:
	WaterShaderProgram(GLuint shaderProgramID);
	~WaterShaderProgram();

	virtual void loadUniformLocations();
	virtual void fillUniformLocation(MeshNode* node, std::vector<LightNode*> lights, bool drawOcclusion = false);
	virtual void fillUniformLocation(LightShaft* lightShaft, LightNode* light);
	virtual void fillUniformLocation(MeshNode* nodem, glm::mat4 modelViewProjectionMatrix, GLuint reflectionTexture, GLuint refractionTexture);

private:
	GLuint locationMVP;
	GLuint locationReflectionTexture;
	GLuint locationRefractionTexture;
};

