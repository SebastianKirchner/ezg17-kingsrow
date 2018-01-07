#pragma once
#include <glad/glad.h>
#include "Shader\ShaderProgram.h"
#include "Importers\ShaderImporter.h"
#include "SceneGraph\LightNode\LightNode.h"


#define SHAFTS_UNIFORM_SIZE 5

class LightNode;

class LightShaft
{
public:
	LightShaft(const MeshLoadInfo::LoadInfo* meshLoadInfo, int width, int height);
	~LightShaft();

	GLuint getTextureArrayColor() { return renderTextureArrayColor; }
	int getSamples() { return samples; }
	GLuint getExposure() { return exposure; }
	GLuint getDecay() { return decay; }
	GLuint getDensity() { return density; }
	GLuint getWeight() { return weight; }

	void normalDrawingPass();
	void occlusionDrawingPass(LightNode* lightShaftLight);
	void composingDrawingPass(glm::mat4 VPmat, LightNode* lightShaftLight);
private:

	int width;
	int height;
	int samples;
	GLfloat exposure;
	GLfloat decay;
	GLfloat density;
	GLfloat weight;
	GLfloat backLightColor;

	ShaderProgram* shaderProgram;								///< Handler of the shader that draws final scene	
	GLuint vertex_loc;							///< Vertex pointer needed for shader
	GLuint texcoord_loc;						///< Texture coordinates pointer needed for shader

	GLuint renderTextureArrayColor;				///< Textures array for color handler
	GLuint renderTextureArrayDepth;				///< Textures array for depth handler
	GLuint frameBuffers[2];						///< Frame buffers for rendering to textures

	GLuint VAO;									///< Vertex array object for shader that renders final scene
	GLuint VBO[2];								///< Vertex buffer object for shader that renders final scene 
												///< (for verticies and texcoodrs)
	GLuint UBO;									///< Uniform buffer object for shader that render final scene 
												///< where light shafts parameters are stored.

	GLint uniformsOffset[SHAFTS_UNIFORM_SIZE];	///< Array that stores offsets of values in uniform buffer
};

