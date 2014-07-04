#include "Display.h"
void Display::Update(){
	unsigned int i;
	do{
		glfwGetWindowSize(window, &this->viewportWidth, &this->viewportHeight);
		glViewport(0, 0, this->viewportWidth, this->viewportHeight);
		glClear(GL_COLOR_BUFFER_BIT);

		//for(i = 0 ; i < objects.size(); i ++){
			objects[0].draw();
			//trimite catre shader matricele de transformate : modelare, vizualizare, proiectie
			// glUniformMatrix4fv(glGetUniformLocation(this->shader_programme,"model_matrix"),1,false, glm::value_ptr(objects[i].model_mat));
			// glUniformMatrix4fv(glGetUniformLocation(this->shader_programme,"view_matrix"),1,false, glm::value_ptr(view_mat));
			// glUniformMatrix4fv(glGetUniformLocation(this->shader_programme,"projection_matrix"),1,false,glm::value_ptr(proj_mat));
		//}
		// Swap buffers
		glfwSwapBuffers(this->window);
		glfwPollEvents();
 
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(this->window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
	glfwWindowShouldClose(this->window) == 0 );
	glfwDestroyWindow(this->window);
	//TODO: DELETE ALL BUFFERS!!!!!!!!
}

Display::Display(int width, int height, char* title)
{
	if (!glfwInit ()){
		fprintf (stderr, "ERROR: could not start GLFW3\n");
		return ;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	this->setWindow(glfwCreateWindow( width, height, title, NULL, NULL));

	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(this->window, (mode->width - width)/2 , (mode->height - height)/2);

	if( this->window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return ;
	}

	glfwMakeContextCurrent(this->window);
	glewExperimental=true; 

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return ;
	}

	this->shader_programme = loadShaderProgramme();

	//activare transparenta
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//incarcam texturile
	std::vector<std::string> textureName;
	textureName.push_back("img.png");
	texIndex = getTextures(textureName);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	view_mat = proj_mat = glm::mat4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);

	Object o(this->shader_programme, texIndex[0]);
	objects.push_back(o);
}

Display::~Display(void)
{
	//destructor
	glfwDefaultWindowHints();
	//glfwDestroyWindow(this->window);
}




char* Display::LoadFileInMemory(const char* filename){

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
GLuint Display::loadShaderProgramme(){

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
GLuint* Display::getTextures(std::vector<std::string> textures){
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
void Display::BindTexture(unsigned int unit, GLuint texCoord){

	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, texCoord);

}

