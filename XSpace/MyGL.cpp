#include "MyGL.h"

void MyGL::init(){
	// init glfw
	if (!glfwInit ()){
		fprintf (stderr, "ERROR: could not start GLFW3\n");
		return ;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
 
	// Open a window and create its OpenGL context 
	 // (In the accompanying source code, this variable is global) 
	window = glfwCreateWindow( 1024, 768, "XSpace", NULL, NULL); 
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return ;
	}
	glfwMakeContextCurrent(window); // Initialize GLEW 
	glewExperimental=true; // Needed in core profile 

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return ;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	loadShaders();

}


void MyGL::run(GLuint vertexbuffer ){
	do{
		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		glViewport(0, 0, windowWidth, windowHeight);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(objects[0].vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objects[0].ibo);
		glDrawElements(GL_TRIANGLES, objects[0].vertexCount, GL_UNSIGNED_SHORT, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
		glBindVertexArray(NULL);
		
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
 
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
	glfwWindowShouldClose(window) == 0 );
	glfwDestroyWindow(window);
	//TODO: DELETE ALL BUFFERS!!!!!!!!
}

MyGL::MyGL(void)
{
}


MyGL::~MyGL(void)
{
}



char * MyGL::LoadFileInMemory(const char* filename){

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

void MyGL::loadShaders(){
	
	const char * vertex_shader = LoadFileInMemory("shaders/vertexShader.glsl");
	const char * fragment_shader = LoadFileInMemory("shaders/fragmentShader.glsl");

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);

	//glBindFragDataLocation(shader_programme, 0, "frag_colour");

	glLinkProgram(shader_programme);
	delete[] vertex_shader;
	delete[] fragment_shader;

	glDeleteShader(vs);
	glDeleteShader(fs);

	glUseProgram(shader_programme);
}