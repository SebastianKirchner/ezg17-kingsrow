#pragma once
#include <glad/glad.h>
#include "Importers\ShaderImporter.h"
#include "SceneGraph\LightNode\LightNode.h"


class Water
{
public:
	Water(int width, int height, float amplitude, float speed);
	~Water();

	void reflectionPass();
	void refractionPass();

	GLuint getReflectionTexture();
	GLuint getRefractionTexture();
	Texture* getDuDvMap();

	GLuint getReflectionFBO();
	GLuint getRefractionFBO();

	float getAmplitude();
	float getSpeed();
	float getTimed();

	void updateWaves(float delta);

private:

	int width;
	int height;
	int samples;

	float amplitude;
	float timed;
	float speed;

	Texture* dudvMap;

	static const int REFL_WIDTH = 1280;
	static const int REFL_HEIGHT = 720;
	static const int REFR_WIDTH = 1280;
	static const int REFR_HEIGHT = 720;

	GLuint vertex_loc;							///< Vertex pointer needed for shader
	GLuint texcoord_loc;						///< Texture coordinates pointer needed for shader

	GLuint fbos[2];

	GLuint reflectionFBO;
	GLuint refractionFBO;

	GLuint reflectionTexture;
	GLuint refractionTexture;

	GLuint reflectionDepthBuffer;
	GLuint refractionDepthTexture;

	GLuint createFBO();
	GLuint createTextureAttachment(int width, int height);
	void initReflection();
	void initRefraction();
	void bindFBO(GLuint fbo, int width, int height);
};

