#pragma once

#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "glm\glm.hpp"
#include "stb_image.h"

#include <iostream>
#include <cassert>
#include <string>
#include <vector>

#include "Object.h"


class Display
{
private:
	GLFWwindow* window;
	GLint viewportHeight;
	GLint viewportWidth;

	//shader
	GLuint shader_programme;

	//objects
	std::vector<Object> objects;
	GLuint* texIndex;

	glm::mat4 view_mat, proj_mat;

public:
	Display(int width, int height,  char* title);
	virtual ~Display(void);

	void Update();

	char * LoadFileInMemory(const char* filename);
	GLuint loadShaderProgramme();
	GLuint* getTextures(std::vector<std::string> textures);
	void BindTexture(unsigned int unit, GLuint texCoord);
	//getters and setters

	//window
	GLFWwindow* getWindow(){return this->window;}
	void setWindow(GLFWwindow *_window){this->window = _window;}
	//viewport
	GLint getViewportWidth(){return this->viewportWidth;}
	void setViewportWidth(GLint _width){this->viewportWidth = _width;}
	GLint getViewportHeight(){return this->viewportHeight;}
	void setViewportHeight(GLint _height){this->viewportHeight = _height;}
	//shaderProgramme
	GLuint getShaderProgramme(){ return this->shader_programme;}
	void setShaderProgramme(GLuint _shaderProgramme){ this->shader_programme = _shaderProgramme;}


};

