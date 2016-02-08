#pragma once

/*OpenGL Libraries*/
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

/*Standard Library*/
#include <string>
#include <memory>

/*Custom Library*/
#include "colour.h"
#include "entity.h"

/*
=====================================

WINDOW

=====================================
*/

class Window
{
public:
	Window							(void);
	Window							(glm::uvec2 size, const std::string& title);
	Window							(unsigned int width, unsigned int height, const std::string& title);
	~Window							(void);

	bool create						(glm::uvec2 size, const std::string& title);
	bool create						(unsigned int width, unsigned int height, const std::string& title);
	void close						(void);

	void draw						(Drawable& entity);
	void draw						(Sprite& sprite);

	void pollEvents					(void);
	void swapBuffers				(void);
	void setClearColour				(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha = 1.0f);
	void setClearColour				(Colour colour);

	GLFWwindow* getRawWindow		(void) const;
	bool isOpen						(void) const;
private:
	GLFWwindow*			_window;
	glm::uvec2			_size;
	std::string			_title;
	bool				_isOpen;
};