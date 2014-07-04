#include "Sprite.h"


boolean Sprite::init(GLfloat* _vertex_buffer, GLushort* _index_buffer, GLuint shader_programme){

	vertex_buffer = _vertex_buffer;
	index_buffer = _index_buffer;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), vertex_buffer, GL_STATIC_DRAW);
	

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLushort), index_buffer, GL_STATIC_DRAW);


	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	positionLoc = glGetAttribLocation(shader_programme, "position");

	glEnableVertexAttribArray(positionLoc);
	glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), NULL);


	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glBindVertexArray(NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	
	free(_vertex_buffer);
	free(_index_buffer);

	vertexCount = 6;
	
	//texturare
	texture_buffer = stbi_load( "img.png", &x, &y, &n, 4);
	if(texture_buffer == NULL)
		std::cout << "ERROR IMAGE loading!!" << std::endl;
	glGenTextures(1, &texture_index);
	glBindTexture(GL_TEXTURE_2D, texture_index);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //ce se intampla cand coordonata nu se inscrie in limite
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); //ce se intampla cand coordonata nu se inscrie in limite
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // setam samplare cu interpolare liniara
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // setam samplare cu interpolare liniara

	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, x,	y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_buffer);
	
	//bind
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_index);

	free(texture_buffer);
	return true;
}


Sprite::Sprite(void)
{
}


Sprite::~Sprite(void)
{
}
