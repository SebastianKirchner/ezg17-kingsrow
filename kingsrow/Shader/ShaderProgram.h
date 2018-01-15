#pragma once
#include <glad/glad.h>
//#include <GL/glew.h>

//forward declaration
#include "../SceneGraph/MeshNode.h"
#include "../SceneGraph/LightNode/LightNode.h"
#include "../LightShaft.h"

class MeshNode;
class Text;
class LightShaft;
class LightNode;


class ShaderProgram
{
public:
	
	ShaderProgram(GLuint shaderProgramID);

	GLuint getShaderId();

	ShaderProgram();
	~ShaderProgram();

	virtual void loadUniformLocations() = 0;
	virtual void fillUniformLocation(MeshNode* node, std::vector<LightNode*> lights, bool drawOcclusion = false) = 0;
	virtual void fillUniformLocation(LightShaft* lightShaft, LightNode* light) = 0;
	virtual void fillUniformLocation(MeshNode* node, glm::mat4 modelViewProjectionMatrix, GLuint reflectionTexture, GLuint refractionTexture) = 0;

protected:
	GLuint programId;
};

