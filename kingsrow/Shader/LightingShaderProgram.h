#pragma once

#include "../Shader/ShaderProgram.h"

class LightingShaderProgram : public ShaderProgram
{
public:
	LightingShaderProgram(GLuint shaderProgramID);
	~LightingShaderProgram();

	virtual void loadUniformLocations();
	virtual void fillUniformLocation(MeshNode* node, std::vector<LightNode*> lights, bool drawOcclusion = false);
	virtual void fillUniformLocation(LightShaft* lightShaft, LightNode* light);
	virtual void fillUniformLocation(MeshNode* nodem, glm::mat4 modelViewProjectionMatrix, Water* water);

	GLuint getLocationMVP();
	GLuint getLocationTexture();
	
private:
	GLuint locationMVP;
	GLuint locationV;
	GLuint locationM;
	GLuint locationLightInvDirection_worldspace;
	GLuint locationDepthBiasMVP;
	

};

