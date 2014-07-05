#include "Object.h"

void Object::draw(){
	glBindVertexArray(vertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArrayObject);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texObject);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glBindVertexArray(NULL);
}


Object::Object(GLint shaderProgramme, GLuint _texObject)
{
	GLfloat vertexBuffer[] = {
		-1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.3f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.3f, 0.3f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.3f, 0.0f, 0.0f, 1.0f,
	};
	GLushort indices[] = {0, 1, 2, 0, 2, 3};

	GLint vertexPosition = glGetAttribLocation(shaderProgramme, "in_position");
	GLint texCoord = glGetAttribLocation(shaderProgramme, "texcoord");
	
	this->vertexCount = 6;

	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);
	
	glGenBuffers(1, &indexArrayObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArrayObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexCount * sizeof(GLushort), &indices[0], GL_STATIC_DRAW);

	//vertex position
	glEnableVertexAttribArray(vertexPosition); 
	glVertexAttribPointer(vertexPosition, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), NULL);
  
	//texture
	glEnableVertexAttribArray(texCoord);
	glVertexAttribPointer(texCoord, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	
	glBindVertexArray(NULL);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	this->texObject = _texObject;
	
}


Object::~Object(void)
{
	glDeleteBuffers(1,&this->vertexBufferObject);
	glDeleteBuffers(1,&this->vertexArrayObject);
	glDeleteBuffers(1,&this->indexArrayObject);
}
