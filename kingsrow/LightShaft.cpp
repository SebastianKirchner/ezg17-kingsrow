#include "LightShaft.h"

// Vertex coordinates of final scene 
GLfloat rect[12] =
{
	-1.0f, -1.0f,
	1.0f, -1.0f,
	1.0f, 1.0f,

	-1.0f, -1.0f,
	1.0f, 1.0f,
	-1.0f, 1.0f
};

// Texture coordinates of final scene
GLfloat texcoords[12] =
{
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f
};

LightShaft::LightShaft(const MeshLoadInfo::LoadInfo* meshLoadInfo, int width, int height)
{
	backLightColor = 0.16;

	glGenTextures(1, &textureArrayColor);
	glGenTextures(1, &textureArrayDepth);

	//render occlusion in it
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureArrayColor);
	glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, width, height, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	//render depth in it
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureArrayDepth);
	glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT, width, height, 2, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);


	glGenFramebuffers(2, frameBuffers);

	// 0: occlusin frambuffer
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffers[0]);
	glFramebufferTextureLayer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureArrayColor, 0, 0);
	glFramebufferTextureLayer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, textureArrayDepth, 0, 0);

	// 1: normal scene framebuffer
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffers[1]);
	glFramebufferTextureLayer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureArrayColor, 0, 1);
	glFramebufferTextureLayer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, textureArrayDepth, 0, 1);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	shaderProgram = ShaderImporter::getInstance()->loadShaderProgram(meshLoadInfo->shaderInfo);
	shaderProgram->loadUniformLocations();

	locationVertex = glGetAttribLocation(shaderProgram->getShaderId(), "position");
	LocationTexCoord = glGetAttribLocation(shaderProgram->getShaderId(), "texCoord");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);
	glVertexAttribPointer(locationVertex, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(locationVertex);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texcoords), texcoords, GL_STATIC_DRAW);
	glVertexAttribPointer(LocationTexCoord, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(LocationTexCoord);

	
	glBindVertexArray(0);
	this->width = width;
	this->height = height;


}


LightShaft::~LightShaft()
{
}

void LightShaft::normalDrawingPass()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffers[1]);
	glViewport(0, 0, width, height);
	glClearColor(0.1, 0.1, 0.4, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void LightShaft::occlusionDrawingPass(LightNode* lightShaftLight)
{
	// Bind and clear the buffer for rendering occlusion
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffers[0]);
	glViewport(0, 0, width, height);
	glClearColor(backLightColor*lightShaftLight->getColor().x,
		backLightColor*lightShaftLight->getColor().y,
		backLightColor*lightShaftLight->getColor().z,
		backLightColor*1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void LightShaft::composingDrawingPass(glm::mat4 VPmat, LightNode * lightShaftLight)
{
	// Bind and clear the buffer (default one) for rendering the final scene
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glViewport(0, 0, width, height);
	glClearColor(0.1, 0.1, 0.4, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/// Get the screen position of point light in (0,1) coordinates. It is needed for future
	/// light shafts calculations in shader (because the whole effect is a post process).
	glm::vec4 lightNDCPosition = VPmat * glm::vec4(lightShaftLight->getPosition(), 1);
	lightNDCPosition /= lightNDCPosition.w;
	glm::vec2 lightScreenPosition = glm::vec2(
		(lightNDCPosition.x + 1) * 0.5,
		(lightNDCPosition.y + 1) * 0.5
	);
	//std::cout << "calculated light location " << lightScreenPosition.x << "; " << lightScreenPosition.y << std::endl;
	lightShaftLight->setLightPositionScreenSpace(lightScreenPosition);
	/// Draw the final scene using the texture array containing the occlusion and normal scene.
	/// Also the screen position of point light is needed. Use vertex buffers with positions and
	/// texture coordinates of quad that fills whole screen.
	GLuint id = shaderProgram->getShaderId();
	glUseProgram(id);
	shaderProgram->fillUniformLocation(this, lightShaftLight);
	//glBindTexture(GL_TEXTURE_2D_ARRAY, renderTextureArrayColor);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	glUseProgram(0);
}
