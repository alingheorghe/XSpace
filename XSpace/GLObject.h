#pragma once
#include "headers\Headers.h"
class GLObject
{
public:
	//Point2D position;

	//
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
	GLint vertexSize;

	GLfloat *vertex_buffer;
	GLushort *index_buffer;

public:
	void init(int _vertexSize, GLfloat* _vertex_buffer, int sizeIndex , GLushort* _index_buffer);
	GLObject(void);
	~GLObject(void);
};

