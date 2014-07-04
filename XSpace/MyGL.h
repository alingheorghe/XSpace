#pragma once
#include "headers\Headers.h"
#include "Sprite.h"
#include <vector>

class MyGL
{
public:
	GLFWwindow* window;
	GLuint shader_programme;
	GLint windowWidth;
	GLint windowHeight;
	std::vector<Sprite> objects;

public:
	void init();
	void run(GLuint vertexbuffer );



	//shader program
	char * LoadFileInMemory(const char* filename);
	void loadShaders();

	MyGL(void);
	~MyGL(void);
};

