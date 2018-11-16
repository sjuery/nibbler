#ifndef EXTERN_OPENGL_HPP
#define EXTERN_OPENGL_HPP
#define GLFW_INCLUDE_GLCOREARB
#define GLM_ENABLE_EXPERIMENTAL
#define NDEBUG
#include "extern.hpp"
#include <GLFW/glfw3.h>

class OpenGLInfo : public GameInfo {
private:
	GLFWwindow* _window;
	GLfloat _triangle[100000];
	int _triangleSize = 0;
	int _shaderprogram;
public:
	OpenGLInfo(coords);
	~OpenGLInfo();

	int getInput();
	void drawBox(struct coords, enum object);
	void display();
};

#endif
