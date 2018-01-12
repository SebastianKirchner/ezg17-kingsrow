#include "LightNode.h"
#include <glm/gtc/type_ptr.hpp>


LightNode::LightNode(int uuid, glm::vec3 position, GLfloat intensity, glm::vec3 color, LightType type) : SceneNode(uuid, NodeType::LIGHT_NODE)
{
	this->position = position;
	this->intensity = intensity;
	this->color = color;
	this->type = type;

	scale = glm::vec2(1.0, (float)1920.0/(float)1080.0);
	shaderProgram = ShaderImporter::getInstance()->loadShaderProgram(MeshLoadInfo::LIGHT_SHAFT_MARKER_SHADER);
	shaderProgram->loadUniformLocations();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	/// Fill the buffer with the vertex data, that is a position of point light.
	/// Only one point is needed, bedause the whole marker will be generated in geometry shader.
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(glGetAttribLocation(shaderProgram->getShaderId(), "inPosition"), 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBufferData(GL_ARRAY_BUFFER, sizeof(position), glm::value_ptr(position), GL_STATIC_DRAW);
	glEnableVertexAttribArray(glGetAttribLocation(shaderProgram->getShaderId(), "inPosition"));

	glBindVertexArray(0);
}

LightNode::~LightNode()
{
}

glm::highp_mat4 LightNode::propagateMatrix()
{
	return parent->propagateMatrix();
}

glm::vec3 LightNode::getPosition()
{
	return position;
}

GLfloat LightNode::getIntensity()
{
	return intensity;
}

glm::vec3 LightNode::getColor()
{
	return color;
}

LightType LightNode::getLightType()
{
	return type;
}

ShaderProgram * LightNode::getShaderProgram()
{
	return shaderProgram;
}

