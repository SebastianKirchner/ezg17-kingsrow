#include "LightShaft.h"

///< Vertex coordinates of final scene (quad filling whole screen)
GLfloat rect[12] =
{
	-1.0f, -1.0f,
	1.0f, -1.0f,
	1.0f, 1.0f,

	-1.0f, -1.0f,
	1.0f, 1.0f,
	-1.0f, 1.0f
};

///< Texture coordinates of final scene (quad filling whole screen)
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
	exposure = 0.0034;
	decay = 0.995;
	density = 0.84;
	weight = 6.65;
	samples = 100;

	// Generate texture handlers for color and depth components
	glGenTextures(1, &renderTextureArrayColor);
	glGenTextures(1, &renderTextureArrayDepth);

	// Make a texture array for color component. This is where occlusion and scenes will be rendered to.
	glBindTexture(GL_TEXTURE_2D_ARRAY, renderTextureArrayColor);
	glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, width, height, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	// Make a texture array for depth component. This is where occlusion and scenes depth buffer will be rendered to.
	glBindTexture(GL_TEXTURE_2D_ARRAY, renderTextureArrayDepth);
	glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT, width, height, 2, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	// Generate two frame buffers that will be used for rendering to textures
	glGenFramebuffers(2, frameBuffers);

	// Bind first frame buffer to the first position of rexture array of color and depth. This is where occlusion will be rendered.
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffers[0]);
	glFramebufferTextureLayer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderTextureArrayColor, 0, 0);
	glFramebufferTextureLayer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, renderTextureArrayDepth, 0, 0);

	// Bind first frame buffer to the second position of rexture array of color and depth. This is where the normal scene will be rendered.
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffers[1]);
	glFramebufferTextureLayer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderTextureArrayColor, 0, 1);
	glFramebufferTextureLayer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, renderTextureArrayDepth, 0, 1);

	// Bind the basic frame buffer for now in order to not make a mess.
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	shaderProgram = ShaderImporter::getInstance()->loadShaderProgram(meshLoadInfo->shaderInfo);
	shaderProgram->loadUniformLocations();

	vertex_loc = glGetAttribLocation(shaderProgram->getShaderId(), "position");
	texcoord_loc = glGetAttribLocation(shaderProgram->getShaderId(), "texCoord");

	/// Generate all necessary buffors for data
	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, VBO);
	glGenBuffers(1, &UBO);

	/// Fill the buffer with the vertex data, that are positions of verticies of quad filling the whole screen.
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);
	glVertexAttribPointer(vertex_loc, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(vertex_loc);

	/// Fill the buffer with the texture coordinates data that are proper for quad filling the whole screen.
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texcoords), texcoords, GL_STATIC_DRAW);
	glVertexAttribPointer(texcoord_loc, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(texcoord_loc);

	
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
	glClearColor(0, 0, 0, 1);
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
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/// Get the screen position of point light in (0,1) coordinates. It is needed for future
	/// light shafts calculations in shader (because the whole effect is a post process).
	glm::vec4 lightNDCPosition = VPmat * glm::vec4(lightShaftLight->getPosition(), 1);
	lightNDCPosition /= lightNDCPosition.w;
	glm::vec2 lightScreenPosition = glm::vec2(
		(lightNDCPosition.x + 1) * 0.5,
		(lightNDCPosition.y + 1) * 0.5
	);
	lightShaftLight->setLightPositionScreenSpace(lightScreenPosition);
	/// Draw the final scene using the texture array containing the occlusion and normal scene.
	/// Also the screen position of point light is needed. Use vertex buffers with positions and
	/// texture coordinates of quad that fills whole screen.
	GLuint id = shaderProgram->getShaderId();
	glUseProgram(id);
	shaderProgram->fillUniformLocation(this, lightShaftLight);
	glBindTexture(GL_TEXTURE_2D_ARRAY, renderTextureArrayColor);

	glBindVertexArray(VAO);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, UBO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	glUseProgram(0);
}
