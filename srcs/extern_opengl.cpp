#include "extern_opengl.hpp"

extern "C" GameInfo* create_object()
{
	return new OpenGLInfo;
}

extern "C" void destroy_object( GameInfo* object )
{
	delete object;
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
