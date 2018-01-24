#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>


//#include <stdio.h>
//#include <stdlib.h>
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
#include "Water.h"
#include <fstream>

const std::vector<std::string> explode(const std::string& s, const char& c)
{
	std::string buff{ "" };
	std::vector<std::string> v;

	for (auto n : s)
	{
		if (n != c) buff += n; else
			if (n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if (buff != "") v.push_back(buff);

	return v;
}

int main() {

	//Update the values also in LightNode, in case these values change
	int viewPortResX = 1280;
	int viewPortResY = 768;
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

	LightNode* light = new PointLightNode(generateUuid(), glm::vec3(0, 8, 10), 1.0, glm::vec3(1, 1, 1));
	
	LightNode* lightSpot1 = new SpotLightNode(generateUuid(), glm::vec3(-5, 2.3, -1.5), 1.f, glm::vec3(1, 1, 1), glm::vec3(0, -1, 0), glm::vec2(10, 9));
	LightNode* lightSpot2 = new SpotLightNode(generateUuid(), glm::vec3(-5, 2.3, 1.5), 1.f, glm::vec3(1, 1, 1), glm::vec3(0, -1, 0), glm::vec2(10, 9));
	LightNode* lightSpot3 = new SpotLightNode(generateUuid(), glm::vec3(-2, 2.3, -1.5), 1.f, glm::vec3(1, 1, 1), glm::vec3(0, -1, 0), glm::vec2(10, 9));
	LightNode* lightSpot4 = new SpotLightNode(generateUuid(), glm::vec3(-2, 2.3, 1.5), 1.f, glm::vec3(1, 1, 1), glm::vec3(0, -1, 0), glm::vec2(10, 9));
	LightNode* lightSpot5 = new SpotLightNode(generateUuid(), glm::vec3(1, 2.3, -1.5), 1.f, glm::vec3(1, 1, 1), glm::vec3(0, -1, 0), glm::vec2(10, 9));
	LightNode* lightSpot6 = new SpotLightNode(generateUuid(), glm::vec3(1, 2.3, 1.5), 1.f, glm::vec3(1, 1, 1), glm::vec3(0, -1, 0), glm::vec2(10, 9));
	LightNode* lightSpot7 = new SpotLightNode(generateUuid(), glm::vec3(4, 2.3, 1.5), 1.f, glm::vec3(1, 1, 1), glm::vec3(0, -1, 0), glm::vec2(10, 9));
	LightNode* lightSpot8 = new SpotLightNode(generateUuid(), glm::vec3(4, 2.3, -1.5), 1.f, glm::vec3(1, 1, 1), glm::vec3(0, -1, 0), glm::vec2(10, 9));
	LightNode* lightSpot9 = new SpotLightNode(generateUuid(), glm::vec3(7, 2.3, 1.5), 1.f, glm::vec3(1, 1, 1), glm::vec3(0, -1, 0), glm::vec2(10, 9));
	LightNode* lightSpot10 = new SpotLightNode(generateUuid(), glm::vec3(7, 2.3, -1.5), 1.f, glm::vec3(1, 1, 1), glm::vec3(0, -1, 0), glm::vec2(10, 9));

	lights1.push_back(light);

	lights1.push_back(lightSpot1);
	lights1.push_back(lightSpot2);
	lights1.push_back(lightSpot3);
	lights1.push_back(lightSpot4);
	lights1.push_back(lightSpot5);
	lights1.push_back(lightSpot6);
	lights1.push_back(lightSpot7);
	lights1.push_back(lightSpot8);
	lights1.push_back(lightSpot9);
	lights1.push_back(lightSpot10);

	std::map<int, std::vector<LightNode*>> lightMap;
	lightMap.insert(std::pair<int, std::vector<LightNode*>>(1, lights1));

	renderer->setLights(lightMap.find(1)->second);
	std::vector<LightNode*> lights = lights1;

	MeshNode* bridgeMesh = MeshImporter::getInstance()->getMesh(MeshLoadInfo::BRIDGE);
	MeshNode* groundMesh = MeshImporter::getInstance()->getMesh(MeshLoadInfo::GROUND);

	MeshNode* treeMesh1 = MeshImporter::getInstance()->getMesh(MeshLoadInfo::TREE);
	MeshNode* treeMesh2 = MeshImporter::getInstance()->getMesh(MeshLoadInfo::TREE);
	MeshNode* treeMesh3 = MeshImporter::getInstance()->getMesh(MeshLoadInfo::TREE);
	MeshNode* treeMesh4 = MeshImporter::getInstance()->getMesh(MeshLoadInfo::TREE);
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
	MeshNode* streetLamp7 = MeshImporter::getInstance()->getMesh(MeshLoadInfo::STREET_LAMP);
	MeshNode* streetLamp8 = MeshImporter::getInstance()->getMesh(MeshLoadInfo::STREET_LAMP);
	MeshNode* streetLamp9 = MeshImporter::getInstance()->getMesh(MeshLoadInfo::STREET_LAMP);
	MeshNode* streetLamp10 = MeshImporter::getInstance()->getMesh(MeshLoadInfo::STREET_LAMP);
	//MeshNode* moonMesh = MeshImporter::getInstance()->getMesh(MeshLoadInfo::MOON);
	MeshNode* plane = MeshImporter::getInstance()->getMesh(MeshLoadInfo::PLANE);
	
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
	streetLamp7->prepareForRendering();
	streetLamp8->prepareForRendering();
	streetLamp9->prepareForRendering();
	streetLamp10->prepareForRendering();
	//moonMesh->prepareForRendering();
	plane->prepareForRendering();

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
	drawArray.push_back(streetLamp7);
	drawArray.push_back(streetLamp8);
	drawArray.push_back(streetLamp9);
	drawArray.push_back(streetLamp10);
	//drawArray.push_back(moonMesh);

	
	SceneNode* sceneGraph = new SceneNode(generateUuid(), NodeType::ROOT_NODE);
	sceneGraph->setParent(nullptr);

	SceneNode* transformNodeGround = new TransformNode(generateUuid(), glm::mat4(
		0, 0, -0.4, 0,
		0, 0.4, 0, 0,
		0.4, 0, 0, 0,
		9, 0, 0, 1));

	SceneNode* transformNodeBridge = new TransformNode(generateUuid(), glm::mat4(
		2.1, 0, 0, 0,
		0, 1.2, 0, 0,
		0, 0, 1, 0,
		18.5, 0, 0, 1));
	SceneNode* transformNodeTree = new TransformNode(generateUuid(), glm::mat4(
		0.4, 0, 0, 0,
		0, 0.4, 0, 0,
		0, 0, 0.4, 0,
		-5, 0, -4.5, 1));
	SceneNode* transformNodeTree2 = new TransformNode(generateUuid(), glm::mat4(
		0.7, 0, -0.2, 0,
		0, 0.7, 0, 0,
		0.2, 0, 0.7, 0,
		-5, 0, 4.5, 1));
	SceneNode* transformNodeTree3 = new TransformNode(generateUuid(), glm::mat4(
		0.7, 0, 0, 0,
		0, 0.7, 0, 0,
		0, 0, 0.7, 0,
		-2, 0, -4.5, 1));
	SceneNode* transformNodeTree4 = new TransformNode(generateUuid(), glm::mat4(
		0.7, 0, 0, 0,
		0, 0.5, 0, 0,
		0, 0, 0.7, 0,
		-2, 0, 4.5, 1));
	SceneNode* transformNodeTree5 = new TransformNode(generateUuid(), glm::mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		1, 0, -4.5, 1));
	SceneNode* transformNodeTree6 = new TransformNode(generateUuid(), glm::mat4(
		0.7, 0, -0.6, 0,
		0, 0.7, 0, 0,
		0.6, 0, 0.7, 0,
		1, 0, 4.5, 1));
	SceneNode* transformNodeTree7 = new TransformNode(generateUuid(), glm::mat4(
		0.7, 0, 0.3, 0,
		0, 0.7, 0, 0,
		-0.3, 0, 0.7, 0,
		4, 0, -4.5, 1));
	SceneNode* transformNodeTree8 = new TransformNode(generateUuid(), glm::mat4(
		0.7, 0, 0, 0,
		0, 0.7, 0, 0,
		0, 0, 0.7, 0,
		4, 0, 4.5, 1));
	SceneNode* transformNodeTree9 = new TransformNode(generateUuid(), glm::mat4(
		0.7, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 0.7, 0,
		7, 0, -4.5, 1));
	SceneNode* transformNodeTree10 = new TransformNode(generateUuid(), glm::mat4(
		0.5, 0, 0, 0,
		0, 0.5, 0, 0,
		0, 0, 0.5, 0,
		7, 0, 4.5, 1));
	SceneNode* transformNodeTree11 = new TransformNode(generateUuid(), glm::mat4(
		0.7, 0, -0.3, 0,
		0, 0.7, 0, 0,
		0.3, 0, 0.7, 0,
		10, 0, -4.5, 1));
	SceneNode* transformNodeTree12 = new TransformNode(generateUuid(), glm::mat4(
		1.2, 0, 0, 0,
		0, 1.2, 0, 0,
		0, 0, 1.2, 0,
		10, 0, 4.5, 1));
	//SceneNode* transformNodeMoon = new TransformNode(generateUuid(), glm::mat4(
	//	0.7, 0, 0.6, 0,
	//	0, 0.7, 0, 0,
	//	-0.6, 0, 0.7, 0,
	//	0, 8, 10, 1));

	SceneNode* streetLampNode1 = new TransformNode(generateUuid(), glm::mat4(
		0, 0, 0.3, 0,
		0, 0.6, 0, 0,
		-0.3, 0, 0, 0,
		-5, 0, -2.5, 1));
	SceneNode* streetLampNode2 = new TransformNode(generateUuid(), glm::mat4(
		0, 0, -0.3, 0,
		0, 0.6, 0, 0,
		0.3, 0, 0, 0,
		-5, 0, 2.5, 1));
	SceneNode* streetLampNode3 = new TransformNode(generateUuid(), glm::mat4(
		0, 0, 0.3, 0,
		0, 0.6, 0, 0,
		-0.3, 0, 0, 0,
		-2, 0, -2.5, 1));
	SceneNode* streetLampNode4 = new TransformNode(generateUuid(), glm::mat4(
		0, 0, -0.3, 0,
		0, 0.6, 0, 0,
		0.3, 0, 0, 0,
		-2, 0, 2.5, 1));
	SceneNode* streetLampNode5 = new TransformNode(generateUuid(), glm::mat4(
		0, 0, 0.3, 0,
		0, 0.6, 0, 0,
		-0.3, 0, 0, 0,
		1, 0, -2.5, 1));
	SceneNode* streetLampNode6 = new TransformNode(generateUuid(), glm::mat4(
		0, 0, -0.3, 0,
		0, 0.6, 0, 0,
		0.3, 0, 0, 0,
		1, 0, 2.5, 1));
	SceneNode* streetLampNode7 = new TransformNode(generateUuid(), glm::mat4(
		0, 0, -0.3, 0,
		0, 0.6, 0, 0,
		0.3, 0, 0, 0,
		4, 0, 2.5, 1));
	SceneNode* streetLampNode8 = new TransformNode(generateUuid(), glm::mat4(
		0, 0, 0.3, 0,
		0, 0.6, 0, 0,
		-0.3, 0, 0, 0,
		4, 0, -2.5, 1));
	SceneNode* streetLampNode9 = new TransformNode(generateUuid(), glm::mat4(
		0, 0, -0.3, 0,
		0, 0.6, 0, 0,
		0.3, 0, 0, 0,
		7, 0, 2.5, 1));
	SceneNode* streetLampNode10 = new TransformNode(generateUuid(), glm::mat4(
		0, 0, 0.3, 0,
		0, 0.6, 0, 0,
		-0.3, 0, 0, 0,
		7, 0, -2.5, 1));

	SceneNode* planeNode = new TransformNode(generateUuid(), glm::mat4(
		2, 0, 0, 0,
		0, 2, 0, 0,
		0, 0, 2, 0,
		19, 0, 1, 1));
	

	planeNode->attachChild(plane);
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
	//transformNodeMoon->attachChild(moonMesh);
	streetLampNode1->attachChild(streetLamp1);
	streetLampNode2->attachChild(streetLamp2);
	streetLampNode3->attachChild(streetLamp3);
	streetLampNode4->attachChild(streetLamp4);
	streetLampNode5->attachChild(streetLamp5);
	streetLampNode6->attachChild(streetLamp6);
	streetLampNode7->attachChild(streetLamp7);
	streetLampNode8->attachChild(streetLamp8);
	streetLampNode9->attachChild(streetLamp9);
	streetLampNode10->attachChild(streetLamp10);

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
	//sceneGraph->attachChild(transformNodeMoon);

	sceneGraph->attachChild(streetLampNode1);
	sceneGraph->attachChild(streetLampNode2);
	sceneGraph->attachChild(streetLampNode3);
	sceneGraph->attachChild(streetLampNode4);
	sceneGraph->attachChild(streetLampNode5);
	sceneGraph->attachChild(streetLampNode6);
	sceneGraph->attachChild(streetLampNode7);
	sceneGraph->attachChild(streetLampNode8);
	sceneGraph->attachChild(streetLampNode9);
	sceneGraph->attachChild(streetLampNode10);

	sceneGraph->attachChild(transformNodeBridge);
	sceneGraph->attachChild(planeNode);

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

	// declare before loop to avoid memory cost
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 invertedViewMatrix;
	glm::mat4 viewProjectionMatrix;
	glm::vec3 playerPosition;

	LightShaft* lightShaft = new LightShaft(MeshLoadInfo::LIGHTSHAFT, viewPortResX, viewPortResY);
	Water* water = new Water(viewPortResX, viewPortResY, 0.01f, 0.02f);

	//std::ofstream myFile;
	//myFile.open("../kingsrow/Assets/CameraMov/directions.txt");
	std::ifstream directionFile("../kingsrow/Assets/CameraMov/directions.txt");
	std::string currentDirectionInputLine;
	//gameloop
	glfwSetCursorPos(renderer->getWindow(), 0, 0);
	while (!input->esc && glfwWindowShouldClose(renderer->getWindow()) == 0) {
		//we do not need this, since we have automatic camera movement
		input->update(renderer->getWindow());

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		time = glfwGetTime();
		double deltaTime = time - oldTime;
		while (deltaTime > timeStep)
		{
			deltaTime -= timeStep;
			sceneGraph->update(timeStep, input);
			
			//myFile << input->w << " " << input->a << " " << input->s << " " << input->d << " " << input->xPos << " " << input->yPos << "\n";
			/*
			
			if (std::getline(directionFile, currentDirectionInputLine)) {
				//w a s d x y\n
				std::vector<std::string> directionComp = explode(currentDirectionInputLine, ' ');
				if (directionComp.size() == 6) {
					if (directionComp.at(0) == "1") {
						input->w = true;
					}
					else {
						input->w = false;
					}
					if (directionComp.at(1) == "1") {
						input->a = true;
					}
					else {
						input->a = false;
					}
					if (directionComp.at(2) == "1") {
						input->s = true;
					}
					else {
						input->s = false;
					}
					if (directionComp.at(3) == "1") {
						input->d = true;
					}
					else {
						input->d = false;
					}
					input->xPos = std::atoi(directionComp.at(4).c_str());
					input->yPos = std::atoi(directionComp.at(5).c_str());
				}
				sceneGraph->update(timeStep, input);
				
			}
			else {
				input->esc = true;
			}
			*/
		}
		
		oldTime = time - deltaTime;

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		projectionMatrix = activeCamera->getProjectionMatrix();
		viewMatrix = activeCamera->getViewMatrix();
		invertedViewMatrix = player->getInvertedViewMatrix(-1.0f);
		viewProjectionMatrix = projectionMatrix * viewMatrix;
		playerPosition = glm::vec3(glm::inverse(viewMatrix)[0][3], glm::inverse(viewMatrix)[1][3], glm::inverse(viewMatrix)[2][3]);

		/*
		 * WATER PASSES
		 */
 		glEnable(GL_CLIP_DISTANCE0);
		 
		water->setCameraPosition(player->getPosition());
		water->setLightPosition(lights.at(0)->getPosition());
		water->reflectionPass();
		for (MeshNode* node : drawArray) {
			//-------------draw-------------------
			node->draw(invertedViewMatrix, projectionMatrix, projectionMatrix * invertedViewMatrix, playerPosition, glm::vec4(0, 1, 0, 0), false);
		}

		water->refractionPass();
		for (MeshNode* node : drawArray) {
			//-------------draw-------------------
			node->draw(viewMatrix, projectionMatrix, viewProjectionMatrix, playerPosition, glm::vec4(0, -1, 0, 0), false);
		}
		glDisable(GL_CLIP_DISTANCE0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, viewPortResX, viewPortResY);

		water->updateWaves(deltaTime);
		// normal drawing pass
		lightShaft->normalDrawingPass();
		
		for (MeshNode* node : drawArray) {
			//-------------draw-------------------
			node->draw(viewMatrix, projectionMatrix, viewProjectionMatrix, player->getPosition(), glm::vec4(0, -1, 0, 0), false);
		}
		renderer->drawWater(plane, viewProjectionMatrix * glm::mat4(plane->propagateMatrix()), water);

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
	//myFile.close();
	directionFile.close();
	glfwTerminate();

	return 0;
}


