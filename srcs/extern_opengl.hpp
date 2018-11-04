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
public:
	OpenGLInfo();
	~OpenGLInfo();

	int getInput();
	void drawBox(struct coords, enum object);
};

#endif
