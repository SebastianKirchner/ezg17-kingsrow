#include "PlayerNode.h"

#include <fstream>
#include <iostream>
#include <string>

#include "TransformNode.h"

PlayerNode::PlayerNode(int uuid) : SceneNode(uuid, NodeType::PLAYER_NODE)
{
	up = glm::vec3(0, 1, 0);
	right = glm::vec3(1, 0, 0);
	direction = glm::vec3(0, 0, 1);
	oldMousePosX = 0;
	oldMousePosY = 0;
}


PlayerNode::~PlayerNode()
{

}

glm::highp_mat4 PlayerNode::propagateMatrix()
{
	return parent->propagateMatrix();
}

void PlayerNode::update(double deltaTime, InputHandler* input)
{
	//if (input->r)
	//	controller->setPosition(physx::PxExtendedVec3(0, 50, 0));
	
	//std::cerr << "view matrix: " << glm::lookAt(position, right, up) << std::endl;
	//std::cerr << "model Matrix: " << propagateMatrix() << std::endl;
	
	if (input->w)
		position += glm::normalize(glm::vec3(direction.x, direction.y, direction.z)) * (float)deltaTime * speed;
	if (input->s)
		position += -glm::normalize(glm::vec3(direction.x, direction.y, direction.z)) * (float)deltaTime * speed;
	if (input->a)
		position += -right * (float)deltaTime * speed;
	if (input->d)
		position += right * (float)deltaTime * speed;

	//position.y = 0;

	//prevent camera from flipping
	if (direction.y > 0.9 && (oldMousePosY - input->yPos) > 0 || direction.y < -0.9 && oldMousePosY - input->yPos < 0)
	{
		updateDirection(deltaTime, oldMousePosX - input->xPos, 0);
		//std::cout << "flip prevention" << std::endl;

	}
	else
	{
		updateDirection(deltaTime, oldMousePosX - input->xPos, oldMousePosY - input->yPos);
		//std::cout << "norm" << std::endl;
	}

	//updateDirection(horizontalAngle, verticalAngle);
	oldMousePosY = input->yPos;
	oldMousePosX = input->xPos;

	TransformNode* node;
	glm::mat4 parentTransform;
	glm::vec3 positionViewHack = glm::vec3(position.x, position.y, position.z);	//bumps up the camera position by 1
	if (parent->getType() == NodeType::TRANSFORM_NODE)
	{
		node = (TransformNode*)parent;
		node->setNewTransform(glm::highp_mat4(glm::lookAt(positionViewHack, positionViewHack + direction, up)));
	}
}

void PlayerNode::updateDirection(double dT, float rotateX, float rotateY)
{
	horizontalAngle += turnSpeed * rotateX;
	verticalAngle += turnSpeed * rotateY;

	direction = glm::vec3(cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle));
	right = glm::vec3(sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f));
	up = glm::cross(right, direction);

}

glm::vec3 PlayerNode::getPosition()
{
	return position;
}

void PlayerNode::setCamera(CameraNode* camera){
	playerCamera = camera;
}

glm::mat4 PlayerNode::getInvertedViewMatrix(float height)
{
	float distance = 2.0f * (position.y - height);
	glm::vec3 invertedPosition = position;
	invertedPosition.y -= distance;
	glm::vec3 invertedDirection = glm::reflect(direction, glm::vec3(0, 1, 0));
	return glm::lookAt(invertedPosition, invertedPosition + invertedDirection, glm::vec3(0, 1, 0));
}