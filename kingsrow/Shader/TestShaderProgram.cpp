#include "TestShaderProgram.h"

#include <iostream>
#include <sstream>
#include <glm\glm.hpp>
#include "..\SceneGraph\LightNode\LightsEnum.h"

TestShaderProgram::TestShaderProgram(GLuint shaderProgramID) : ShaderProgram(shaderProgramID)
{
}


TestShaderProgram::~TestShaderProgram()
{
}

void TestShaderProgram::loadUniformLocations()
{
	locationLightScreenPos = glGetUniformLocation(programId, "lightScreenPos");
	locationTex = glGetUniformLocation(programId, "tex");
	locationSamples = glGetUniformLocation(programId, "params.samples");
	locationExposure = glGetUniformLocation(programId, "params.exposure");
	locationDecay = glGetUniformLocation(programId, "params.decay");
	locationDensity = glGetUniformLocation(programId, "params.density");
	locationWeight = glGetUniformLocation(programId, "params.weight");
}

void TestShaderProgram::fillUniformLocation(MeshNode* node, std::vector<LightNode*> lights, bool drawOcclusion)
{
}

void TestShaderProgram::fillUniformLocation(LightShaft * lightShaft, LightNode * light)
{
	glUniform2f(locationLightScreenPos, light->getLightPositionScreenSpace().x, light->getLightPositionScreenSpace().y);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, lightShaft->getTextureArrayColor());
	glUniform1i(locationTex, 0);
	glUniform1i(locationSamples, lightShaft->getSamples());
	glUniform1f(locationExposure, lightShaft->getExposure());
	glUniform1f(locationDecay, lightShaft->getDecay());
	glUniform1f(locationDensity, lightShaft->getDensity());
	glUniform1f(locationWeight, lightShaft->getWeight());
}

void TestShaderProgram::fillUniformLocation(MeshNode* node, glm::mat4 modelViewProjectionMatrix, GLuint reflectionTexture, GLuint refractionTexture)
{
}