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
	reflectionTexture = glGetUniformLocation(programId, "reflectionTexture");
	refractionTexture = glGetUniformLocation(programId, "refractionTexture");
}

void WaterShaderProgram::fillUniformLocation(MeshNode* node, std::vector<LightNode*> lights, bool drawOcclusion)
{
	glm::mat4 MVP = node->getModelViewProjectionMatrix();
	glUniformMatrix4fv(locationMVP, 1, GL_FALSE, &MVP[0][0]);
}

void WaterShaderProgram::fillUniformLocation(LightShaft * lightShaft, LightNode * light)
{
}

void WaterShaderProgram::fillUniformLocation(MeshNode* node, glm::mat4 modelViewProjectionMatrix, GLuint reflectionTexture, GLuint refractionTexture)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, reflectionTexture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, refractionTexture);
	glm::mat4 MVP = modelViewProjectionMatrix;
	glUniformMatrix4fv(locationMVP, 1, GL_FALSE, &MVP[0][0]);
}