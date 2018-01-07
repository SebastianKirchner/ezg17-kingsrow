#pragma once

#include "..\Shader\ShaderProgram.h"


class LightShaftMarkerShaderProgram : public ShaderProgram
{
public:
	LightShaftMarkerShaderProgram(GLuint shaderProgramID);
	~LightShaftMarkerShaderProgram();

	virtual void loadUniformLocations();
	virtual void fillUniformLocation(MeshNode* node, std::vector<LightNode*> lights, bool drawOcclusion = false);
	virtual void fillUniformLocation(LightShaft* lightShaft, LightNode* light);

private:
	GLuint locationViewProkectionMatrix;
	GLuint locationScale;
	GLuint locationColor;
};

