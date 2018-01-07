#pragma once
#include <glad/glad.h>
#include "Shader\ShaderProgram.h"
#include "Importers\ShaderImporter.h"
#include "SceneGraph\LightNode\LightNode.h"


class Water
{
public:
	Water(const MeshLoadInfo::LoadInfo* meshLoadInfo, int width, int height);
	~Water();

	void reflectionPass();
	void refractionPass();

private:

	int width;
	int height;
	int samples;

	static const int REFL_WIDTH = 320;
	static const int REFL_HEIGHT = 180;
	static const int REFR_WIDTH = 1280;
	static const int REFR_HEIGHT = 720;

	ShaderProgram* shaderProgram;				///< Handler of the shader that draws final scene	

	GLuint vertex_loc;							///< Vertex pointer needed for shader
	GLuint texcoord_loc;						///< Texture coordinates pointer needed for shader

	GLuint fbos[2];

	GLuint reflectionFBO;
	GLuint refractionFBO;

	GLuint reflectionTexture;
	GLuint refractionTexture;

	GLuint reflectionDepthBuffer;
	GLuint refractionDepthTexture;

	void initReflection();
	void initRefraction();
	void bindFBO(GLuint fbo, int width, int height);
};

