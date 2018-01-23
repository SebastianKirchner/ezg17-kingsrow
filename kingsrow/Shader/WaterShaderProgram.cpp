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
	locationNormalMap = glGetUniformLocation(programId, "normalMap");
	locationAmplitude = glGetUniformLocation(programId, "amplitude");
	locationSpeed = glGetUniformLocation(programId, "speed");
	locationCameraPosition = glGetUniformLocation(programId, "cameraPos"); 
	locationM = glGetUniformLocation(programId, "M");
	locationLightPosition = glGetUniformLocation(programId, "lightPos");
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
	
	glUniform1i(locationNormalMap, 3);
	glActiveTexture(GL_TEXTURE0 + 3);
	glBindTexture(GL_TEXTURE_2D, water->getNormalMap()->getTextureID());
	
	glUniformMatrix4fv(locationMVP, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(locationM, 1, GL_FALSE, &glm::mat4(node->getModelMatrix())[0][0]);
	glUniform1f(locationAmplitude, water->getAmplitude());
	glUniform1f(locationSpeed, water->getTimed());
	
	glm::vec3 cameraPosition = water->getCameraPosition();
	glUniform3f(locationCameraPosition, cameraPosition.x, cameraPosition.y, cameraPosition.z);	
	
	glm::vec3 lightPosition = water->getLightPosition();
	glUniform3f(locationLightPosition, lightPosition.x, lightPosition.y, lightPosition.z);
	
	cameraPosition = glm::normalize(cameraPosition);
	glm::vec4 inModel = glm::normalize(glm::mat4(node->getModelMatrix()) * glm::vec4(cameraPosition, 1.0));
	//printf("(%f, %f, %f)\n", inModel.x, inModel.y, inModel.z);
}