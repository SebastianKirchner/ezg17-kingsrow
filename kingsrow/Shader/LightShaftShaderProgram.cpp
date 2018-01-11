#include "LightShaftShaderProgram.h"



LightShaftShaderProgram::LightShaftShaderProgram(GLuint shaderProgramID) : ShaderProgram(shaderProgramID)
{
}


LightShaftShaderProgram::~LightShaftShaderProgram()
{
}

void LightShaftShaderProgram::loadUniformLocations()
{
	locationLightScreenPos = glGetUniformLocation(programId, "lightScreenPos");
	locationTex = glGetUniformLocation(programId, "tex");
	locationSamples = glGetUniformLocation(programId, "params.samples");
	locationExposure = glGetUniformLocation(programId, "params.exposure");
	locationDecay = glGetUniformLocation(programId, "params.decay");
	locationDensity = glGetUniformLocation(programId, "params.density");
	locationWeight = glGetUniformLocation(programId, "params.weight");
}

void LightShaftShaderProgram::fillUniformLocation(MeshNode * node, std::vector<LightNode*> lights, bool drawOcclusion)
{
}

void LightShaftShaderProgram::fillUniformLocation(LightShaft * lightShaft, LightNode* light)
{
	glUniform2f(locationLightScreenPos, light->getLightPositionScreenSpace().x, light->getLightPositionScreenSpace().y);
	//std::cout << light->getLightPositionScreenSpace().x << ", " << light->getLightPositionScreenSpace().y << std::endl;
	glBindTexture(GL_TEXTURE_2D_ARRAY, lightShaft->getTextureArrayColor());
	//glActiveTexture(GL_TEXTURE0);
	
	glUniform1i(locationTex, 0);
	glUniform1i(locationSamples, lightShaft->getSamples());
	glUniform1f(locationExposure, lightShaft->getExposure());
	glUniform1f(locationDecay, lightShaft->getDecay());
	glUniform1f(locationDensity, lightShaft->getDensity());
	glUniform1f(locationWeight, lightShaft->getWeight());
}
