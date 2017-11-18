#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>


#include <stdio.h>
#include <stdlib.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <map>
#include <sstream>

#include "InputHandler.h"
#include "Render\Renderer.h"
#include "Util\UuidHelper.h"
#include "Importers\MeshImporter.h"
#include "SceneGraph\TransformNode.h"
#include "SceneGraph\LightNode\LightsEnum.h"
#include "SceneGraph\CameraNode.h"
#include "SceneGraph\PlayerNode.h"
#include "SceneGraph\LightNode\PointLightNode.h"
#include "SceneGraph\LightNode\DirectionalLightNode.h"
#include "SceneGraph\LightNode\SpotLightNode.h"
#include "Texture\SamplerStateEnum.h"
#include "Texture\MipmapStateEnum.h"


int main() {

	int viewPortResX = 1024 * 3;
	int viewPortResY = 756 * 3;
	Renderer* renderer = Renderer::getInstance();
	if (renderer->init(viewPortResX, viewPortResY) == -1) {
		return -1;
	}

	InputHandler* input = new InputHandler();


	//Texture* rainbowTexture = new Texture("../kingsrow/Assets/Models/duck_textures/rainbow.jpg");

	std::map<std::string, CameraNode*> cameraList;

	//start of part that should be in a scene loader
	CameraNode* activeCamera = new CameraNode(generateUuid(), viewPortResX, viewPortResY);


	//this way we have a list of cameras and can switch between them as we want just by doing activeCamera = cameraList.find("whichever camera we want")->second;
	cameraList.insert(std::pair<std::string, CameraNode*>(std::string("player camera"), activeCamera));


	std::vector<LightNode*> lights1;
	//room 1
	LightNode* lightSpot1 = new SpotLightNode(generateUuid(), glm::vec3(1, 1, 1), 1.0f, glm::vec3(1, 0, 0), glm::vec3(0, -1, 0), glm::vec2(1, 0.8));
	LightNode* lightSpot2 = new SpotLightNode(generateUuid(), glm::vec3(-1, 1, 1), 1.0f, glm::vec3(0, 0, 1), glm::vec3(0, -1, 0), glm::vec2(1, 0.8));
	LightNode* lightSpot3 = new SpotLightNode(generateUuid(), glm::vec3(-1, 1, -1), 1.0f, glm::vec3(0, 1, 0), glm::vec3(0, -1, 0), glm::vec2(1, 0.8));
	LightNode* lightSpot4 = new SpotLightNode(generateUuid(), glm::vec3(1, 1, -1), 1.0f, glm::vec3(1, 0, 1), glm::vec3(0, -1, 0), glm::vec2(1, 0.8));
	LightNode* lightDir1 = new DirectionalLightNode(generateUuid(), glm::vec3(4, 5, -4), 1.0f, glm::vec3(1, 1, 1), glm::vec3(0, -1, 0));

	lights1.push_back(lightSpot1);
	lights1.push_back(lightSpot2);
	lights1.push_back(lightSpot3);
	lights1.push_back(lightSpot4);
	lights1.push_back(lightDir1);

	std::map<int, std::vector<LightNode*>> lightMap;
	lightMap.insert(std::pair<int, std::vector<LightNode*>>(1, lights1));

	renderer->setLights(lightMap.find(1)->second);
	std::vector<LightNode*> lights = lights1;

	MeshNode* bridgeMesh = MeshImporter::getInstance()->getMesh(MeshLoadInfo::BRIDGE);
	MeshNode* treeMesh1 = MeshImporter::getInstance()->getMesh(MeshLoadInfo::TREE);
	MeshNode* treeMesh2 = MeshImporter::getInstance()->getMesh(MeshLoadInfo::TREE);
	MeshNode* treeLeaf1 = MeshImporter::getInstance()->getMesh(MeshLoadInfo::TREELEAF);
	MeshNode* cubeMap = MeshImporter::getInstance()->getMesh(MeshLoadInfo::CUBEMAP);



	bridgeMesh->prepareForRendering();
	treeMesh1->prepareForRendering();
	treeMesh2->prepareForRendering();
	treeLeaf1->prepareForRendering();
	cubeMap->prepareForRendering();


	std::vector<MeshNode*> drawArray;
	drawArray.push_back(bridgeMesh);
	drawArray.push_back(treeMesh1);
	drawArray.push_back(treeMesh2);
	drawArray.push_back(treeLeaf1);
	drawArray.push_back(cubeMap);


	SceneNode* sceneGraph = new SceneNode(generateUuid(), NodeType::ROOT_NODE);
	sceneGraph->setParent(nullptr);


	SceneNode* transformNodeBridge = new TransformNode(generateUuid(), glm::mat4(
		1.5, 0, 0, 0,
		0, 1.2, 0, 0,
		0, 0, 1, 0,
		0, -1, 0, 1));
	SceneNode* transformNodeTree = new TransformNode(generateUuid(), glm::mat4(
		0.8, 0, 0, 0,
		0, 0.8, 0, 0,
		0, 0, 0.8, 0,
		0, -2, -4, 1));
	SceneNode* transformNodeTree2 = new TransformNode(generateUuid(), glm::mat4(
		0.6, 0, 0, 0,
		0, 0.6, 0, 0,
		0, 0, 0.6, 0,
		-6, -2, -4, 1));
	SceneNode* transformNodeTreeLeaf1 = new TransformNode(generateUuid(), glm::mat4(
		0.6, 0, 0, 0,
		0, 0.6, 0, 0,
		0, 0, 0.6, 0,
		-2, -3, -3, 1));
	SceneNode* transformNodeCubeMap = new TransformNode(generateUuid(), glm::mat4(
		0.6, 0, 0, 0,
		0, 0.6, 0, 0,
		0, 0, 0.6, 0,
		0, 6.7, 0, 1));



	transformNodeBridge->attachChild(bridgeMesh);
	transformNodeTree->attachChild(treeMesh1);
	transformNodeTree2->attachChild(treeMesh2);
	transformNodeTreeLeaf1->attachChild(treeLeaf1);
	transformNodeCubeMap->attachChild(cubeMap);

	sceneGraph->attachChild(transformNodeBridge);
	sceneGraph->attachChild(transformNodeTree);
	sceneGraph->attachChild(transformNodeTree2);
	sceneGraph->attachChild(transformNodeTreeLeaf1);
	sceneGraph->attachChild(transformNodeCubeMap);

	SceneNode* playerTransform = new TransformNode(generateUuid(), glm::mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		2, 0, -2.5, 1));

	PlayerNode* player = new PlayerNode(generateUuid());
	player->setCamera(activeCamera);
	playerTransform->attachChild(activeCamera);
	playerTransform->attachChild(player);
	sceneGraph->attachChild(playerTransform);

	//should probably done recursively in sceneNode		

	//end of part that should be in a scene loader

	double time = glfwGetTime();
	double oldTime = glfwGetTime();
	double timeStep = 1.0 / 60.0;
	double timeOld = 0;

	//gameloop
	while (!input->esc && glfwWindowShouldClose(renderer->getWindow()) == 0) {
		input->update(renderer->getWindow());

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		time = glfwGetTime();
		double deltaTime = time - oldTime;
		while (deltaTime > timeStep)
		{
			deltaTime -= timeStep;
			sceneGraph->update(timeStep, input);
		}
		oldTime = time - deltaTime;

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		


		glm::mat4 projectionMatrix = activeCamera->getProjectionMatrix();
		glm::mat4 viewMatrix = activeCamera->getViewMatrix();
		glm::mat4 viewProjectionMatrix = projectionMatrix * viewMatrix;
		glm::vec3 playerPosition = glm::vec3(glm::inverse(viewMatrix)[0][3], glm::inverse(viewMatrix)[1][3], glm::inverse(viewMatrix)[2][3]);

		//draw meshes
		for (MeshNode* node : drawArray) {
			//-------------draw-------------------
			node->draw(viewMatrix, projectionMatrix, viewProjectionMatrix, player->getPosition());
		}

		glfwSwapBuffers(renderer->getWindow());
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}


