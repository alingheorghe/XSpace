#pragma once
#include "glm\glm.hpp"
#include "GL\glew.h"

class Vertex
{
private:
		glm::vec3 position;
		glm::vec2 texCoord;
public:
	Vertex(const glm::vec3& _position, const glm::vec2 _texCoord){
		this->position = _position;
		this->texCoord = _texCoord;
	}

	inline glm::vec3* getPosition() { return &this->position; }
	inline glm::vec2* getTexCoord() { return &this->texCoord; }
};

class Mesh
{
private:
	GLuint vertexArrayObject;
	GLuint vertexBufferObject;
	GLuint indexArrayObject;
	GLuint texObject;

	int vertexCount;

public:
	void draw();
	Mesh(Vertex* vertices,Vertex* indexs,unsigned int numVertices, unsigned int numIndexs);
	virtual ~Mesh(void);
};

