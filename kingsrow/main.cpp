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
#include "LightShaft.h"

int main() {

	//Update the values also in LightNode, in case these values change
	int viewPortResX = 1920;
	int viewPortResY = 1080;
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
	//LightNode* lightSpot1 = new SpotLightNode(generateUuid(), glm::vec3(-5, 2.8, -3.7), 1.0f, glm::vec3(1, 0, 0), glm::vec3(0, -1, 0), glm::vec2(5, 1));
	//LightNode* lightSpot2 = new SpotLightNode(generateUuid(), glm::vec3(-5, 2.8, 3.7), 1.0f, glm::vec3(0, 0, 1), glm::vec3(0, -1, 0), glm::vec2(5, 1));
	//LightNode* lightSpot3 = new SpotLightNode(generateUuid(), glm::vec3(1, 2.8, -3.7), 1.0f, glm::vec3(0, 1, 0), glm::vec3(0, -1, 0), glm::vec2(5, 2));
	//LightNode* lightSpot4 = new SpotLightNode(generateUuid(), glm::vec3(1, 2.8, 3.7), 1.0f, glm::vec3(0, 0, 1), glm::vec3(0, -1, 0), glm::vec2(5, 2));
	//LightNode* lightSpot5 = new SpotLightNode(generateUuid(), glm::vec3(0, 2.8, 0), 1.0f, glm::vec3(0, 1, 0), glm::vec3(0, -1, 0), glm::vec2(5, 2));
	//LightNode* lightSpot6 = new SpotLightNode(generateUuid(), glm::vec3(0, 2.8, 1), 1.0f, glm::vec3(1, 0, 0), glm::vec3(0, -1, 0), glm::vec2(5, 2));
	//LightNode* lightDir1 = new DirectionalLightNode(generateUuid(), glm::vec3(-5, 5, 0), 1.0f, glm::vec3(0.0, 0.0, 0.0), glm::vec3(1, -1, 0));

	//LightNode* light = new PointLightNode(generateUuid(), glm::vec3(-5, 2.8, -3.7), 1.0, glm::vec3(1, 1, 1));
	LightNode* light = new PointLightNode(generateUuid(), glm::vec3(0, 0, 0), 1.0, glm::vec3(1, 1, 1));
	lights1.push_back(light);
	/*lights1.push_back(lightSpot1);
	lights1.push_back(lightSpot2);
	lights1.push_back(lightSpot3);
	lights1.push_back(lightSpot4);
	lights1.push_back(lightSpot5);
	lights1.push_back(lightSpot6);
	lights1.push_back(lightDir1);*/

	std::map<int, std::vector<LightNode*>> lightMap;
	lightMap.insert(std::pair<int, std::vector<LightNode*>>(1, lights1));

	renderer->setLights(lightMap.find(1)->second);
	std::vector<LightNode*> lights = lights1;

	/*MeshNode* bridgeMesh = MeshImporter::getInstance()->getMesh(MeshLoadInfo::BRIDGE);
	MeshNode* groundMesh = MeshImporter::getInstance()->getMesh(MeshLoadInfo::GROUND);

	MeshNode* treeMesh1 = MeshImporter::getInstance()->getMesh(MeshLoadInfo::TREE);
	MeshNode* treeMesh2 = MeshImporter::getInstance()->getMesh(MeshLoadInfo::TREE);
	MeshNode* treeMesh3 = MeshImporter::getInstance()->getMesh(MeshLoadInfo::TREE);
	MeshNode* treeMesh4= MeshImporter::getInstance()->getMesh(MeshLoadInfo::TREE);
	MeshNode* treeMesh5 = MeshImporter::getInstance()->getMesh(MeshLoadInfo::TREE);
	MeshNode* treeMesh6 = MeshImporter::getInstance()->getMesh(MeshLoadInfo::TREE);
	MeshNode* treeMesh7 = MeshImporter::getInstance()->getMesh(MeshLoadInfo::TREE);
	MeshNode* treeMesh8 = MeshImporter::getInstance()->getMesh(MeshLoadInfo::TREE);
	MeshNode* treeMesh9 = MeshImporter::getInstance()->getMesh(MeshLoadInfo::TREE);
	MeshNode* treeMesh10 = MeshImporter::getInstance()->getMesh(MeshLoadInfo::TREE);
	MeshNode* treeMesh11= MeshImporter::getInstance()->getMesh(MeshLoadInfo::TREE);
	MeshNode* treeMesh12 = MeshImporter::getInstance()->getMesh(MeshLoadInfo::TREE);
	
	MeshNode* streetLamp1 = MeshImporter::getInstance()->getMesh(MeshLoadInfo::STREET_LAMP);
	MeshNode* streetLamp2 = MeshImporter::getInstance()->getMesh(MeshLoadInfo::STREET_LAMP);
	MeshNode* streetLamp3 = MeshImporter::getInstance()->getMesh(MeshLoadInfo::STREET_LAMP);
	MeshNode* streetLamp4 = MeshImporter::getInstance()->getMesh(MeshLoadInfo::STREET_LAMP);
	MeshNode* streetLamp5 = MeshImporter::getInstance()->getMesh(MeshLoadInfo::STREET_LAMP);
	MeshNode* streetLamp6 = MeshImporter::getInstance()->getMesh(MeshLoadInfo::STREET_LAMP);
	
	MeshNode* cubeMap = MeshImporter::getInstance()->getMesh(MeshLoadInfo::CUBEMAP);

	bridgeMesh->prepareForRendering();
	groundMesh->prepareForRendering();
	treeMesh1->prepareForRendering();
	treeMesh2->prepareForRendering();
	treeMesh3->prepareForRendering();
	treeMesh4->prepareForRendering();
	treeMesh5->prepareForRendering();
	treeMesh6->prepareForRendering();
	treeMesh7->prepareForRendering();
	treeMesh8->prepareForRendering();
	treeMesh9->prepareForRendering();
	treeMesh10->prepareForRendering();
	treeMesh11->prepareForRendering();
	treeMesh12->prepareForRendering();
	streetLamp1->prepareForRendering();
	streetLamp2->prepareForRendering();
	streetLamp3->prepareForRendering();
	streetLamp4->prepareForRendering();
	streetLamp5->prepareForRendering();
	streetLamp6->prepareForRendering();


	cubeMap->prepareForRendering();

	std::vector<MeshNode*> drawArray;
	drawArray.push_back(bridgeMesh);
	drawArray.push_back(groundMesh);
	drawArray.push_back(treeMesh1);
	drawArray.push_back(treeMesh2);
	drawArray.push_back(treeMesh3);
	drawArray.push_back(treeMesh4);
	drawArray.push_back(treeMesh5);
	drawArray.push_back(treeMesh6);
	drawArray.push_back(treeMesh7);
	drawArray.push_back(treeMesh8);
	drawArray.push_back(treeMesh9);
	drawArray.push_back(treeMesh10);
	drawArray.push_back(treeMesh11);
	drawArray.push_back(treeMesh12);
	drawArray.push_back(streetLamp1);
	drawArray.push_back(streetLamp2);
	drawArray.push_back(streetLamp3);
	drawArray.push_back(streetLamp4);
	drawArray.push_back(streetLamp5);
	drawArray.push_back(streetLamp6);
	drawArray.push_back(cubeMap);

	*/
	SceneNode* sceneGraph = new SceneNode(generateUuid(), NodeType::ROOT_NODE);
	sceneGraph->setParent(nullptr);


	MeshNode* teapot = MeshImporter::getInstance()->getMesh(MeshLoadInfo::TEAPOT);
	teapot->prepareForRendering();
	std::vector<MeshNode*> drawArray;
	drawArray.push_back(teapot);
	SceneNode* transformTeapotNode = new TransformNode(generateUuid(), glm::mat4(
		0.4, 0, 0, 0,
		0, 0.4, 0, 0,
	    0, 0, 0.4, 0,
		0, 0, 2, 1));
	transformTeapotNode->attachChild(teapot);
	sceneGraph->attachChild(transformTeapotNode);




	/*
	SceneNode* transformNodeGround = new TransformNode(generateUuid(), glm::mat4(
		0, 0, -0.4, 0,
		0, 0.4, 0, 0,
		0.4, 0, 0, 0,
		9, -0.95, 0, 1));

	SceneNode* transformNodeBridge = new TransformNode(generateUuid(), glm::mat4(
		1.5, 0, 0, 0,
		0, 1.2, 0, 0,
		0, 0, 1, 0,
		19, -1, 0, 1));
	SceneNode* transformNodeTree = new TransformNode(generateUuid(), glm::mat4(
		0.7, 0, 0, 0,
		0, 0.7, 0, 0,
		0, 0, 0.7, 0,
		-5, -1, -4.5, 1));
	SceneNode* transformNodeTree2 = new TransformNode(generateUuid(), glm::mat4(
		0.7, 0, 0, 0,
		0, 0.7, 0, 0,
		0, 0, 0.7, 0,
		-5, -1, 4.5, 1));
	SceneNode* transformNodeTree3 = new TransformNode(generateUuid(), glm::mat4(
		0.7, 0, 0, 0,
		0, 0.7, 0, 0,
		0, 0, 0.7, 0,
		-2, -1, -4.5, 1));
	SceneNode* transformNodeTree4 = new TransformNode(generateUuid(), glm::mat4(
		0.7, 0, 0, 0,
		0, 0.7, 0, 0,
		0, 0, 0.7, 0,
		-2, -1, 4.5, 1));
	SceneNode* transformNodeTree5 = new TransformNode(generateUuid(), glm::mat4(
		0.7, 0, 0, 0,
		0, 0.7, 0, 0,
		0, 0, 0.7, 0,
		1, -1, -4.5, 1));
	SceneNode* transformNodeTree6 = new TransformNode(generateUuid(), glm::mat4(
		0.7, 0, 0, 0,
		0, 0.7, 0, 0,
		0, 0, 0.7, 0,
		1, -1, 4.5, 1));
	SceneNode* transformNodeTree7 = new TransformNode(generateUuid(), glm::mat4(
		0.7, 0, 0, 0,
		0, 0.7, 0, 0,
		0, 0, 0.7, 0,
		4, -1, -4.5, 1));
	SceneNode* transformNodeTree8 = new TransformNode(generateUuid(), glm::mat4(
		0.7, 0, 0, 0,
		0, 0.7, 0, 0,
		0, 0, 0.7, 0,
		4, -1, 4.5, 1));
	SceneNode* transformNodeTree9 = new TransformNode(generateUuid(), glm::mat4(
		0.7, 0, 0, 0,
		0, 0.7, 0, 0,
		0, 0, 0.7, 0,
		7, -1, -4.5, 1));
	SceneNode* transformNodeTree10 = new TransformNode(generateUuid(), glm::mat4(
		0.7, 0, 0, 0,
		0, 0.7, 0, 0,
		0, 0, 0.7, 0,
		7, -1, 4.5, 1));
	SceneNode* transformNodeTree11 = new TransformNode(generateUuid(), glm::mat4(
		0.7, 0, 0, 0,
		0, 0.7, 0, 0,
		0, 0, 0.7, 0,
		10, -1, -4.5, 1));
	SceneNode* transformNodeTree12 = new TransformNode(generateUuid(), glm::mat4(
		0.7, 0, 0, 0,
		0, 0.7, 0, 0,
		0, 0, 0.7, 0,
		10, -1, 4.5, 1));
	
	SceneNode* transformNodeCubeMap = new TransformNode(generateUuid(), glm::mat4(
		4, 0, 0, 0,
		0, 2.5, 0, 0,
		0, 0, 2.5, 0,
		0, 0, 0, 1));

	SceneNode* streetLampNode1 = new TransformNode(generateUuid(), glm::mat4(
		0, 0, 0.3, 0,
		0, 0.6, 0, 0,
		-0.3, 0, 0, 0,
		-5, -1, -4.5, 1));
	SceneNode* streetLampNode2 = new TransformNode(generateUuid(), glm::mat4(
		0, 0, -0.3, 0,
		0, 0.6, 0, 0,
		0.3, 0, 0, 0,
		-5, -1, 4.5, 1));
	SceneNode* streetLampNode3 = new TransformNode(generateUuid(), glm::mat4(
		0, 0, 0.3, 0,
		0, 0.6, 0, 0,
		-0.3, 0, 0, 0,
		-2, -1, -4.5, 1));
	SceneNode* streetLampNode4 = new TransformNode(generateUuid(), glm::mat4(
		0, 0, -0.3, 0,
		0, 0.6, 0, 0,
		0.3, 0, 0, 0,
		-2, -1, 4.5, 1));
	SceneNode* streetLampNode5 = new TransformNode(generateUuid(), glm::mat4(
		0, 0, 0.3, 0,
		0, 0.6, 0, 0,
		-0.3, 0, 0, 0,
		1, -1, -4.5, 1));
	SceneNode* streetLampNode6 = new TransformNode(generateUuid(), glm::mat4(
		0, 0, -0.3, 0,
		0, 0.6, 0, 0,
		0.3, 0, 0, 0,
		1, -1, 4.5, 1));

	transformNodeBridge->attachChild(bridgeMesh);
	transformNodeGround->attachChild(groundMesh);

	transformNodeTree->attachChild(treeMesh1);
	transformNodeTree2->attachChild(treeMesh2);
	transformNodeTree3->attachChild(treeMesh3);
	transformNodeTree4->attachChild(treeMesh4);
	transformNodeTree5->attachChild(treeMesh5);
	transformNodeTree6->attachChild(treeMesh6);
	transformNodeTree7->attachChild(treeMesh7);
	transformNodeTree8->attachChild(treeMesh8);
	transformNodeTree9->attachChild(treeMesh9);
	transformNodeTree10->attachChild(treeMesh10);
	transformNodeTree11->attachChild(treeMesh11);
	transformNodeTree12->attachChild(treeMesh12);
	transformNodeCubeMap->attachChild(cubeMap);
	streetLampNode1->attachChild(streetLamp1);
	streetLampNode2->attachChild(streetLamp2);
	streetLampNode3->attachChild(streetLamp3);
	streetLampNode4->attachChild(streetLamp4);
	streetLampNode5->attachChild(streetLamp5);
	streetLampNode6->attachChild(streetLamp6);

	sceneGraph->attachChild(transformNodeGround);
	sceneGraph->attachChild(transformNodeTree);
	sceneGraph->attachChild(transformNodeTree2);
	sceneGraph->attachChild(transformNodeTree3);
	sceneGraph->attachChild(transformNodeTree4);
	sceneGraph->attachChild(transformNodeTree5);
	sceneGraph->attachChild(transformNodeTree6);
	sceneGraph->attachChild(transformNodeTree7);
	sceneGraph->attachChild(transformNodeTree8);
	sceneGraph->attachChild(transformNodeTree9);
	sceneGraph->attachChild(transformNodeTree10);
	sceneGraph->attachChild(transformNodeTree11);
	sceneGraph->attachChild(transformNodeTree12);

	sceneGraph->attachChild(streetLampNode1);
	sceneGraph->attachChild(streetLampNode2);
	sceneGraph->attachChild(streetLampNode3);
	sceneGraph->attachChild(streetLampNode4);
	sceneGraph->attachChild(streetLampNode5);
	sceneGraph->attachChild(streetLampNode6);

	sceneGraph->attachChild(transformNodeBridge);
	sceneGraph->attachChild(transformNodeCubeMap);
*/
	SceneNode* playerTransform = new TransformNode(generateUuid(), glm::mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1));

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

	LightShaft* lightShaft = new LightShaft(MeshLoadInfo::LIGHTSHAFT, viewPortResX, viewPortResY);

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

		lightShaft->normalDrawingPass();
		for (MeshNode* node : drawArray) {
			//-------------draw-------------------
			node->draw(viewMatrix, projectionMatrix, viewProjectionMatrix, player->getPosition(), false);
		}

		lightShaft->occlusionDrawingPass(lights.at(0));
		
		renderer->drawLightMarker(drawArray.at(0), lights.at(0));
		for (MeshNode* node : drawArray) {
			//-------------draw-------------------
			renderer->draw(node, true);
		}
		//compose
		lightShaft->composingDrawingPass(viewProjectionMatrix, lights.at(0));

		glfwSwapBuffers(renderer->getWindow());
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}


