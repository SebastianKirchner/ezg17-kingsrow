#pragma once

#include "..\Shader\ShaderProgram.h"


class LightShaftShaderProgram : public ShaderProgram
{
public:
	LightShaftShaderProgram(GLuint shaderProgramID);
	~LightShaftShaderProgram();

	virtual void loadUniformLocations();
	virtual void fillUniformLocation(MeshNode* node, std::vector<LightNode*> lights, bool drawOcclusion = false);
	virtual void fillUniformLocation(LightShaft* lightShaft, LightNode* light);

private:
	GLuint locationLightScreenPos;
	GLuint locationTex;
};

