#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "glm\glm.hpp"
#include "stb_image.h"

#include <iostream>
#include <cassert>
#include <string>
#include <vector>

char * LoadFileInMemory(const char* filename){

	int size = 0;
	char *buffer = NULL;
	FILE *f = fopen(filename, "rb");
	if (f == NULL)
	{
		return NULL;
	}
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	buffer = new char[size + 1];
	if (size != fread(buffer, sizeof(char), size, f))
	{
		delete[] buffer;
	}
	fclose(f);
	buffer[size] = 0;
	return buffer;

}
GLuint getShaderProgramme(){

	const char * vertex_shader = LoadFileInMemory("shaders/vertexShader.glsl");
	const char * fragment_shader = LoadFileInMemory("shaders/fragmentShader.glsl");

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);

	glBindFragDataLocation(shader_programme, 0, "frag_colour");

	glLinkProgram(shader_programme);
	delete[] vertex_shader;
	delete[] fragment_shader;

	glDeleteShader(vs);
	glDeleteShader(fs);

	return shader_programme;
}
GLuint* getTextures(std::vector<std::string> textures){
	int width, height, numComponents;
	int size = textures.size();

	GLuint* texObjects = new GLuint[size];
	unsigned char *textureBuffer;

	glGenTextures(size, texObjects);
	for(int i = 0 ; i < size; i ++){
		textureBuffer = stbi_load( textures[i].c_str(), &width, &height, &numComponents, 4);
		if(textureBuffer == NULL)
			std::cerr << "Texture " << textures[i].c_str() << " failed to load!" << std::endl;
		glBindTexture(GL_TEXTURE_2D, texObjects[i]);
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width,	height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureBuffer);

		textureBuffer = NULL;
	}
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //ce se intampla cand coordonata nu se inscrie in limite
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); //ce se intampla cand coordonata nu se inscrie in limite
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // setam samplare cu interpolare liniara
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // setam samplare cu interpolare liniara

	free(textureBuffer);

	return texObjects;
}
void BindTexture(unsigned int unit, GLuint texCoord){

	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, texCoord);

}