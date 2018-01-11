#include "Water.h"

///< Vertex coordinates of final scene (quad filling whole screen)
GLfloat quad[12] =
{
	-1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, 1.0f
};

Water::Water(ShaderProgram* shaderProgram, int width, int height)
{
	this->shaderProgram = shaderProgram;
	this->width = width;
	this->height = height;

	this->initReflection();
	this->initRefraction();
	glUseProgram(shaderProgram->getShaderId());
	// bind textures
	glUniform1i(reflectionTexture, 0);
	glUniform1i(refractionTexture, 1);
	glUseProgram(0);
}

void Water::initReflection() 
{
	// create reflectino framebuffer
	glGenFramebuffers(1, &reflectionFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, reflectionFBO);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);

	// create reflection texture
	glGenTextures(1, &reflectionTexture);
	glBindTexture(GL_TEXTURE_2D, reflectionTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, REFL_WIDTH, REFL_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, reflectionTexture, 0);

	// create depth buffer
	glGenRenderbuffers(1, &reflectionDepthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, reflectionDepthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, REFL_WIDTH,
		REFL_HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
		GL_RENDERBUFFER, reflectionDepthBuffer);

	// reset to default fbo
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, this->width, this->height);
}

void Water::initRefraction()
{
	// create refraction framebuffer
	glGenFramebuffers(1, &refractionFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, refractionFBO);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);

	// create refraction texture
	glGenTextures(1, &refractionTexture);
	glBindTexture(GL_TEXTURE_2D, refractionTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, REFR_WIDTH, REFR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, refractionTexture, 0);

	// create depth texture
	glGenTextures(1, &refractionDepthTexture);
	glBindTexture(GL_TEXTURE_2D, refractionDepthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height,
		0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
		refractionDepthTexture, 0);

	// reset to default fbo
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, this->width, this->height);
}

void Water::reflectionPass()
{
	this->bindFBO(reflectionFBO, REFL_WIDTH, REFL_HEIGHT);
}

void Water::refractionPass()
{
	this->bindFBO(refractionFBO, REFR_WIDTH, REFR_HEIGHT);
}

void Water::bindFBO(GLuint fbo, int width, int height)
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glViewport(0, 0, width, height);
}

Water::~Water()
{
	glDeleteFramebuffers(1, &reflectionFBO);
	glDeleteTextures(1, &reflectionTexture);
	glDeleteRenderbuffers(1, &reflectionDepthBuffer);
	glDeleteFramebuffers(1, &refractionFBO);
	glDeleteTextures(1, &refractionTexture);
	glDeleteTextures(1, &refractionDepthTexture);
}

ShaderProgram* Water::getShaderProgram()
{
	return shaderProgram;
}

GLuint Water::getReflectionTexture()
{
	return reflectionTexture;
}

GLuint Water::getRefractionTexture()
{
	return refractionTexture;
}