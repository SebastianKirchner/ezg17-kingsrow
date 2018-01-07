#include "LightShaftMarkerShaderProgram.h"
#include <glm/gtc/type_ptr.hpp>



LightShaftMarkerShaderProgram::LightShaftMarkerShaderProgram(GLuint shaderProgramID) : ShaderProgram(shaderProgramID)
{
}


LightShaftMarkerShaderProgram::~LightShaftMarkerShaderProgram()
{
}

void LightShaftMarkerShaderProgram::loadUniformLocations()
{
	locationViewProkectionMatrix = glGetUniformLocation(programId, "viewProjectionMatrix");
	locationScale = glGetUniformLocation(programId, "scale");
	locationColor = glGetUniformLocation(programId, "color");
}

void LightShaftMarkerShaderProgram::fillUniformLocation(MeshNode * node, std::vector<LightNode*> lights, bool drawOcclusion)
{
	//use only the first light
	glUniformMatrix4fv(locationViewProkectionMatrix, 1, GL_FALSE, glm::value_ptr(node->getViewProjectionMatrix()));
	glm::vec2 scale = lights.at(0)->getScale();
	glUniform2fv(locationScale, 1, glm::value_ptr(scale));
	glUniform4f(locationColor, lights.at(0)->getColor().x, lights.at(0)->getColor().y, lights.at(0)->getColor().z, 1.0);
}

void LightShaftMarkerShaderProgram::fillUniformLocation(LightShaft * lightShaft, LightNode * light)
{
}
