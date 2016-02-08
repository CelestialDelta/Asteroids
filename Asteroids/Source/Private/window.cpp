#include "..\Public\window.h"

/*
=====================================

WINDOW

=====================================
*/

Window::Window(void)
	: _window(nullptr), _size(), _title(), _isOpen(false)
{
}

Window::Window(glm::uvec2 size, const std::string& title)
	: _window(nullptr), _size(), _title(), _isOpen(false)
{
	create(size, title);
}

Window::Window(GLuint width, GLuint height, const std::string& title)
	: _window(nullptr), _size(), _title(title), _isOpen(false)
{
	create(width, height, title);
}

Window::~Window()
{
	close();
}

bool Window::create(glm::uvec2 size, const std::string& title)
{
	_window = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
	if (_window)
	{
		_isOpen = true;
		_size = size;
		_title = title;
		glfwMakeContextCurrent(_window);
		return true;
	}
	else
	{
		return false;
	}
}

bool Window::create(GLuint width, GLuint height, const std::string& title)
{
	_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (_window)
	{
		_isOpen = true;
		_size = glm::uvec2(width, height);
		_title = title;
		glfwMakeContextCurrent(_window);
		return true;
	}
	else
	{
		return false;
	}
}

void Window::close(void)
{
	if (_window)
	{
		glfwDestroyWindow(_window);
		_isOpen = false;
	}
}

void Window::draw(Drawable& entity)
{
	entity.draw();
}

void Window::draw(Sprite& sprite)
{
	sprite.draw();
}

void Window::pollEvents(void)
{
	glfwPollEvents();
	
}

void Window::swapBuffers(void)
{
	glfwSwapBuffers(_window);
}

void Window::setClearColour(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
}

void Window::setClearColour(Colour colour)
{
	glClearColor
		(
		colour.components.red,
		colour.components.green,
		colour.components.blue,
		colour.components.alpha
		);
}

GLFWwindow* Window::getRawWindow(void) const
{
	return _window;
}

bool Window::isOpen(void) const
{
	return !glfwWindowShouldClose(_window);
}