#pragma once

#include "LightNode.h"

class SpotLightNode : public LightNode
{
public:
	SpotLightNode(int uuid, glm::vec3 position, GLfloat intensity, glm::vec3 color, glm::vec3 direction, glm::vec2 cutOff);
	~SpotLightNode();

	glm::vec3 getDirection();
	glm::vec2 getCutOff();

private:

	glm::vec3 direction;
	glm::vec2 cutOff;
};

