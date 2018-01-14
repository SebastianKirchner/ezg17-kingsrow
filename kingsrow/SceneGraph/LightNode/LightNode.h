#pragma once

#include "../SceneNode.h"
#include "LightsEnum.h"
#include "../../Shader/ShaderProgram.h"
#include "../../Importers/ShaderImporter.h"

class ShaderProgram;

class LightNode : public SceneNode
{
public:
	LightNode(int uuid, glm::vec3 position, GLfloat intensity, glm::vec3 color, LightType type);
	~LightNode();

	glm::highp_mat4 propagateMatrix();

	glm::vec3 getPosition();
	GLfloat getIntensity();
	glm::vec3 getColor();
	LightType getLightType();
	virtual glm::vec3 getDirection() = 0;
	virtual glm::vec2 getCutOff() = 0;

	glm::vec2 getScale() { return scale; }
	ShaderProgram* getShaderProgram();
	GLuint getVAO() { return VAO; }
	void setLightPositionScreenSpace(glm::vec2 pos) { lightPositionScreenspace = pos; }
	glm::vec2 getLightPositionScreenSpace() { return lightPositionScreenspace; }

private:
	glm::vec3 position;
	glm::vec2 lightPositionScreenspace;
	GLfloat intensity;
	glm::vec3 color;
	LightType type;

	ShaderProgram* shaderProgram;
	glm::vec2 scale;
	GLuint VAO;			
	GLuint VBO;			
};

