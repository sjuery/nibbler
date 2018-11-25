#include "extern_opengl.hpp"
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

extern "C" GameInfo* create_object( coords dimensions )
{
	return new OpenGLInfo(dimensions);
}

extern "C" void destroy_object( GameInfo* object )
{
	delete object;
}

static const GLfloat vertex_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f,  1.0f, 0.0f,
};

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){
	const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position.xyz = aPos;\n"
    "	gl_Position.w = 1.0;\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec3 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec3(1.0f, 0.0f, 0.0f);\n"
    "}\n\0";
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	int success;
	char infoLog[512];

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	// char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &vertexShaderSource , NULL);
	glCompileShader(VertexShaderID);
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(VertexShaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	// char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &fragmentShaderSource , NULL);
	glCompileShader(FragmentShaderID);
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(FragmentShaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Link the program
	printf("Linking program\n");
	int ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ProgramID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

OpenGLInfo::OpenGLInfo(coords dimensions) : _dimen(dimensions)
{
	if (!glfwInit())
	{
	    std::cout << "Couldn't open window" << std::endl;
		exit(1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	_window = glfwCreateWindow(_dimen.x*5, _dimen.y*5, "LearnOpenGL", NULL, NULL);
	if (_window == NULL)
	{
	    std::cout << "Failed to create GLFW window" << std::endl;
	    glfwTerminate();
	    exit(1);
	}
	glfwMakeContextCurrent(_window);

	//Vertex Array
	GLuint VAO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
	_shaderprogram = LoadShaders("srcs/shader.frag", "srcs/shader.vert");
	// _shaderprogram = LoadShaders("srcs/shader.vert", "srcs/shader.frag");
	// unsigned int VAO;
	// glGenVertexArrays(1, &VAO);
	// glGenBuffers(1, &_VBO);
	// glBindVertexArray(VAO);
	// glEnableVertexAttribArray(0);
	// glEnable(GL_PROGRAM_POINT_SIZE);
	// glPointSize(10);
	// glBindBuffer(GL_ARRAY_BUFFER, 0);
	// glBindVertexArray(VAO);
}

OpenGLInfo::~OpenGLInfo()
{
	glfwTerminate();
}

void OpenGLInfo::display()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	glUseProgram(_shaderprogram);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);
	glfwSwapBuffers(_window);
	glfwPollEvents();
	// std::fill(_square, _square+_squareSize, 0);
	// _squareSize = 0;
}

void OpenGLInfo::drawBox(struct coords crds, enum object type)
{
	// _square[_squareSize++] = crds.x/(_dimen.x*5.0f)*1.0f - 1;
	// _square[_squareSize++] = crds.y/(_dimen.y*5.0f)*-1.0f + 1;
	// _square[_squareSize++] = .0f;
	(void)type;
	(void)crds;
}

int OpenGLInfo::getInput()
{
	if(glfwGetKey(_window, '1'))
		return ONE;
	if(glfwGetKey(_window, '2'))
		return TWO;
	if(glfwGetKey(_window, '3'))
		return THREE;
	if(glfwGetKey(_window, GLFW_KEY_UP))
		return UP;
	if(glfwGetKey(_window, GLFW_KEY_DOWN))
		return DOWN;
	if(glfwGetKey(_window, GLFW_KEY_LEFT))
		return LEFT;
	if(glfwGetKey(_window, GLFW_KEY_RIGHT))
		return RIGHT;
	return '0';
}
