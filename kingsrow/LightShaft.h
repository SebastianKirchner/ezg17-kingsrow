#pragma once
#include <glad/glad.h>
#include "Shader\ShaderProgram.h"
#include "Importers\ShaderImporter.h"
#include "SceneGraph\LightNode\LightNode.h"

class LightNode;

class LightShaft
{
public:
	LightShaft(const MeshLoadInfo::LoadInfo* meshLoadInfo, int width, int height);
	~LightShaft();

	GLuint getTextureArrayColor() { return textureArrayColor; }

	void normalDrawingPass();
	void occlusionDrawingPass(LightNode* lightShaftLight);
	void composingDrawingPass(glm::mat4 VPmat, LightNode* lightShaftLight);
private:

	int width;
	int height;
	GLfloat backLightColor;

	ShaderProgram* shaderProgram;								
	GLuint locationVertex;							
	GLuint LocationTexCoord;						

	GLuint textureArrayColor;				
	GLuint textureArrayDepth;				
	GLuint frameBuffers[2];						

	GLuint VAO;									
	GLuint VBO[2];								
};

