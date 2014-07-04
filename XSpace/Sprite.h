#pragma once
#include "headers\Headers.h"
#include "glm\glm.hpp"
#include "stb_image.h"

class Sprite
{
public:
	glm::vec3 position;
	glm::vec3 aspectRatio;

	//object index
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
	GLuint texture_index;
	int vertexCount;

	//shader stuff
	GLuint shader_programme;
	GLuint positionLoc;

	//buffers
	GLfloat* vertex_buffer;
	GLushort* index_buffer;

	unsigned char* texture_buffer;

	//texture struff
	int x, y, n;
	int force_channels;
	
public:
	boolean init(GLfloat* _vertex_buffer, GLushort* _index_buffer, GLuint shader_programme);
	Sprite(void);
	~Sprite(void);
};

