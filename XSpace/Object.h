#pragma once
#include "glm\glm.hpp"
#include "GL\glew.h"
#include <iostream>

class Object
{
private:
	GLuint vertexArrayObject;
	GLuint vertexBufferObject;
	GLuint indexArrayObject;
	GLuint texObject;

	int vertexCount;

public:
	void draw();
	Object(GLint shaderProgramme, GLuint _texObject);
	~Object(void);
};

