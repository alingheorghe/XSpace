#include "Mesh.h"


//------------Mesh-----------
void Mesh::draw(){
	glBindVertexArray(this->vertexArrayObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexArrayObject);
	glDrawElements(GL_TRIANGLES, this->vertexCount, GL_UNSIGNED_SHORT, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	glBindVertexArray(NULL);
}


Mesh::Mesh()
{
	GLfloat vertexBuffer[] = {
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.3f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.3f, 0.3f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.3f, 0.0f, 0.0f, 1.0f
	  };

	glGenBuffers(1, &this->vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	

	glGenBuffers(1, &this->indexArrayObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArrayObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndexs * sizeof(indexs[0]), indexs, GL_STATIC_DRAW);


	glGenVertexArrays(1, &this->vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	//positionLoc = glGetAttribLocation(shader_programme, "position");

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), NULL);


	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glBindVertexArray(NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
}


Mesh::~Mesh(void)
{
}
