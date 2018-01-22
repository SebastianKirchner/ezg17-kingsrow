#include "WaterShaderProgram.h"

#include <iostream>
#include <glm\glm.hpp>


WaterShaderProgram::WaterShaderProgram(GLuint shaderProgramID) : ShaderProgram(shaderProgramID)
{
}


WaterShaderProgram::~WaterShaderProgram()
{
}


void WaterShaderProgram::loadUniformLocations()
{
	locationMVP = glGetUniformLocation(programId, "MVP");
	locationReflectionTexture = glGetUniformLocation(programId, "reflectionTexture");
	locationRefractionTexture = glGetUniformLocation(programId, "refractionTexture");
	locationDudvMap = glGetUniformLocation(programId, "dudvMap");
	locationAmplitude = glGetUniformLocation(programId, "amplitude");
	locationSpeed = glGetUniformLocation(programId, "speed");
}

void WaterShaderProgram::fillUniformLocation(MeshNode* node, std::vector<LightNode*> lights, bool drawOcclusion)
{
	glm::mat4 MVP = node->getModelViewProjectionMatrix();
	glUniformMatrix4fv(locationMVP, 1, GL_FALSE, &MVP[0][0]);
}

void WaterShaderProgram::fillUniformLocation(LightShaft * lightShaft, LightNode * light)
{
}

void WaterShaderProgram::fillUniformLocation(MeshNode* node, glm::mat4 modelViewProjectionMatrix, Water* water)
{
	//glBindFramebuffer(GL_FRAMEBUFFER, water->getReflectionFBO());
	glUniform1i(locationReflectionTexture,  0);
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, water->getReflectionTexture());

	// bind refraction texture to texture location 1 of water shader
	//glBindFramebuffer(GL_FRAMEBUFFER, water->getRefractionFBO());
	glUniform1i(locationRefractionTexture, 1);
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, water->getRefractionTexture());

	// reset to default fbo
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glm::mat4 MVP = modelViewProjectionMatrix;
	glUniform1i(locationDudvMap, 2);
	glActiveTexture(GL_TEXTURE0 + 2);
	glBindTexture(GL_TEXTURE_2D, water->getDuDvMap()->getTextureID());
	glUniformMatrix4fv(locationMVP, 1, GL_FALSE, &MVP[0][0]);
	glUniform1f(locationAmplitude, water->getAmplitude());
	glUniform1f(locationSpeed, water->getTimed());

	
}