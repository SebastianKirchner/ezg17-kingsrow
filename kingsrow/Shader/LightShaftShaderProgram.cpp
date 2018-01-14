#include "LightShaftShaderProgram.h"



LightShaftShaderProgram::LightShaftShaderProgram(GLuint shaderProgramID) : ShaderProgram(shaderProgramID)
{
}


LightShaftShaderProgram::~LightShaftShaderProgram()
{
}

void LightShaftShaderProgram::loadUniformLocations()
{
	locationLightScreenPos = glGetUniformLocation(programId, "lightPosScreenSpace");
	locationTex = glGetUniformLocation(programId, "tex");
}

void LightShaftShaderProgram::fillUniformLocation(MeshNode * node, std::vector<LightNode*> lights, bool drawOcclusion)
{
}

void LightShaftShaderProgram::fillUniformLocation(LightShaft * lightShaft, LightNode* light)
{
	glUniform2f(locationLightScreenPos, light->getLightPositionScreenSpace().x, light->getLightPositionScreenSpace().y);
	glBindTexture(GL_TEXTURE_2D_ARRAY, lightShaft->getTextureArrayColor());	
	glUniform1i(locationTex, 0);
}
