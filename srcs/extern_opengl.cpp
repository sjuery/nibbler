#include "extern_opengl.hpp"
#include <fstream>

extern "C" GameInfo* create_object( coords dimensions )
{
	(void)dimensions;
	return new OpenGLInfo;
}

extern "C" void destroy_object( GameInfo* object )
{
	delete object;
}

int LoadShaders(const char * vertex_file_path,const char * fragment_file_path){
	const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// std::ifstream ifs(vertex_file_path);
  	// std::string VertexShaderCode( (std::istreambuf_iterator<char>(ifs) ),
    //                    (std::istreambuf_iterator<char>()    ) );
	// std::ifstream ifs { vertex_file_path };
	// std::string VertexShaderCode { std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };
	// std::ifstream ifss { fragment_file_path };
	// std::string FragmentShaderCode { std::istreambuf_iterator<char>(ifss), std::istreambuf_iterator<char>() };


	// std::cout << FragmentShaderCode << VertexShaderCode << std::endl;
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

	// glDetachShader(ProgramID, VertexShaderID);
	// glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

OpenGLInfo::OpenGLInfo()
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
	_window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (_window == NULL)
	{
	    std::cout << "Failed to create GLFW window" << std::endl;
	    glfwTerminate();
	    exit(1);
	}
	glfwMakeContextCurrent(_window);
}

OpenGLInfo::~OpenGLInfo()
{
	glfwTerminate();
}

void OpenGLInfo::display()
{
}

void OpenGLInfo::drawBox(struct coords crds, enum object type)
{
	float triangle[] = {
		0.1f,  0.1f, 0.0f,
		0.1f, -0.1f, 0.0f,
		-0.1f, -0.1f, 0.0f,
		-0.1f,  0.1f, 0.0f
	};
	unsigned int position[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3,    // second triangle
};
	int shaderprogram = LoadShaders("srcs/shader.vert", "srcs/shader.frag");

	unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while(!glfwWindowShouldClose(_window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shaderprogram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glfwSwapBuffers(_window);
		glfwPollEvents();
	}

	// glUseProgram(LoadShaders("shader.vert", "shader.frag"));
	// glBindVertexArray(VAO);
	// glDrawArrays(GL_TRIANGLES, 0, 3);
	// (void)triangle;
	(void)crds;
	(void)type;
}

int OpenGLInfo::getInput()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(_window);
	glfwPollEvents();

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
