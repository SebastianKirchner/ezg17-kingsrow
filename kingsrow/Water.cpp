#include "Water.h"

Water::Water(int width, int height, float amplitude, float speed)
{
	this->width = width;
	this->height = height;
	this->amplitude = amplitude;
	this->speed = speed;

	std::string dudvMapPath = "../kingsrow/Assets/Models/textures/waterDuDv.png";
	std::string normalMapPath = "../kingsrow/Assets/Models/textures/waterNormal.png";
	dudvMap = new Texture((dudvMapPath).c_str());
	normalMap = new Texture((normalMapPath).c_str());
	initReflection();
	initRefraction();
}

void Water::initReflection() 
{
	// create reflection FBO
	reflectionFBO = createFBO();
	reflectionTexture = createTextureAttachment(REFL_WIDTH, REFL_HEIGHT);
	
	// create depth render buffer
	GLuint depthRenderbuffer;
	glGenRenderbuffers(1, &depthRenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, REFL_WIDTH, REFL_HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer);
	reflectionDepthBuffer = depthRenderbuffer;

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "ERROR::FRAMEBUFFER:: REFLECTION FBO is not complete!" << std::endl;
	}
	
	// reset to default fbo
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, this->width, this->height);
}

void Water::initRefraction()
{
	// create refraction framebuffer
	refractionFBO = createFBO();
	refractionTexture = createTextureAttachment(REFR_WIDTH, REFR_HEIGHT);
	
	// create depth texture
	GLuint depthTexture;
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, REFR_WIDTH, REFR_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
	refractionDepthTexture = depthTexture;
	
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "ERROR::FRAMEBUFFER:: REFRACTION FBO is not complete!" << std::endl;
	}

	// reset to default fbo
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, this->width, this->height);
}

void Water::reflectionPass()
{
	this->bindFBO(reflectionFBO, REFL_WIDTH, REFL_HEIGHT);
	//glClearColor(1, 0, 0, 1);
}

void Water::refractionPass()
{
	this->bindFBO(refractionFBO, REFR_WIDTH, REFR_HEIGHT);
	//glClearColor(0, 1, 0, 1);
}

void Water::bindFBO(GLuint fbo, int width, int height)
{
	glEnable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Water::~Water()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &reflectionFBO);
	glDeleteTextures(1, &reflectionTexture);
	glDeleteRenderbuffers(1, &reflectionDepthBuffer);
	glDeleteFramebuffers(1, &refractionFBO);
	glDeleteTextures(1, &refractionTexture);
	glDeleteTextures(1, &refractionDepthTexture);
}

GLuint Water::createFBO()
{
	GLuint fbo;
	glGenFramebuffers(1, &fbo); 
	glBindFramebuffer(GL_FRAMEBUFFER, fbo); 
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	return fbo;
}

GLuint Water::createTextureAttachment(int width, int height)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0); 
	return texture;
}

GLuint Water::getReflectionTexture()
{
	return reflectionTexture;
}

GLuint Water::getRefractionTexture()
{
	return refractionTexture;
}

GLuint Water::getReflectionFBO()
{
	return reflectionFBO;
}

GLuint Water::getRefractionFBO()
{
	return refractionFBO;
}

Texture* Water::getDuDvMap() {
	return dudvMap;
}

Texture* Water::getNormalMap() {
	return normalMap;
}

float Water::getAmplitude() {
	return amplitude;
}

float Water::getSpeed() {
	return speed;
}

void Water::updateWaves(float delta) {
	timed += speed + delta;
	timed = std::fmod(timed, 1.0f);
}

float Water::getTimed() {
	return timed;
}

glm::vec3 Water::getCameraPosition() 
{
	return cameraPosition;
}

void Water::setCameraPosition(glm::vec3 cameraPosition)
{
	this->cameraPosition = cameraPosition;
}

glm::vec3 Water::getLightPosition()
{
	return lightPosition;
}

void Water::setLightPosition(glm::vec3 lightPosition)
{
	this->lightPosition = lightPosition;
}