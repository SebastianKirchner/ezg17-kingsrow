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
	//reflectionTexture = glGetUniformLocation(programId, "reflectionTexture");
	//refractionTexture = glGetUniformLocation(programId, "refractionTexture");
	// bind textures
}

void WaterShaderProgram::fillUniformLocation(MeshNode* node, std::vector<LightNode*> lights, bool drawOcclusion)
{
	glm::mat4 MVP = node->getModelViewProjectionMatrix();
	glUniformMatrix4fv(locationMVP, 1, GL_FALSE, &MVP[0][0]);
}

void WaterShaderProgram::fillUniformLocation(LightShaft * lightShaft, LightNode * light)
{
}
