#include "Object.h"

void Object::draw(){
	glBindVertexArray(this->vertexArrayObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexArrayObject);
	glDrawElements(GL_TRIANGLES, this->vertexCount, GL_UNSIGNED_SHORT, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	glBindVertexArray(NULL);
}


Object::Object(GLint shaderProgramme, GLuint _texObject)
{
	GLfloat vertexBuffer[] = {
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.3f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.3f, 0.3f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.3f, 0.0f, 0.0f, 1.0f,
	};
	GLushort indices[] = {0, 1, 2, 0, 2, 3};

	GLint vertexPosition = glGetAttribLocation(shaderProgramme, "in_position");
	GLint texCoord = glGetAttribLocation(shaderProgramme, "texCoord");
	
	std::cout << texCoord << " " << 6 * sizeof(GLushort);
	
	this->vertexCount = 6;

	glGenVertexArrays(1, &this->vertexArrayObject);
	glBindVertexArray(this->vertexArrayObject);

	glGenBuffers(1, &this->vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer) * sizeof(GLfloat), vertexBuffer, GL_STATIC_DRAW);
	
	glGenBuffers(1, &this->indexArrayObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexArrayObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexCount * sizeof(GLushort), indices, GL_STATIC_DRAW);

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
