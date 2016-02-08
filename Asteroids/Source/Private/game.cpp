#include "..\Public\game.h"

/*
=====================================

GAME

=====================================
*/

/*Public Methods*/
Game::Game(void)
{
	if (!_initGLFW())
	{
		_terminate("GLFW");
	}
	if (!_initWindow())
	{
		_terminate("Window");
	}
	if (!_initGL())
	{
		_terminate("OpenGL");
	}
	if (!_initResourceCache())
	{
		_terminate("ResourceCache");
	}
	if (!_initShader())
	{
		_terminate("Shader");
	}
}

void Game::init(void)
{
	float delta = 0.f;
	float lastFrame = 0.f;

	ImageResource* image = _cache.load<ImageResource>(HashString("Resource/Images/player.png"));
	ImageResource* project = _cache.load<ImageResource>(HashString("Resource/Images/laser.png"));
	Texture texture(image);
	Texture projectileTexture(project);

	Player player(&_window, &_world, _shader, image, projectileTexture);

	while (_window.isOpen())
	{
		float currentFrame = glfwGetTime();
		delta = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glClear(GL_COLOR_BUFFER_BIT);

		//player.draw();
		handle(delta);
		update(delta);
		draw();
		player.draw();
		/*if (glfwGetKey(_window.getRawWindow(), GLFW_KEY_W) == GLFW_PRESS)
		{
			player.move(delta);
		}
		if (glfwGetKey(_window.getRawWindow(), GLFW_KEY_S) == GLFW_PRESS)
		{
			player.slowDown(delta);
		}
		if (glfwGetKey(_window.getRawWindow(), GLFW_KEY_D) == GLFW_PRESS)
		{
			player.rotateClockwise(delta);
		}
		if (glfwGetKey(_window.getRawWindow(), GLFW_KEY_A) == GLFW_PRESS)
		{
			player.rotateCounterclockwise(delta);
		}*/
		_window.swapBuffers();
		_window.pollEvents();
	}
	glfwTerminate();
}

void Game::handle(float delta)
{
	if (glfwGetKey(_window.getRawWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{
		
	}
	/*if (glfwGetKey(_context->window->raw(), GLFW_KEY_S) == GLFW_PRESS)
	{
		_context->player->move_backward(delta);
	}
	if (glfwGetKey(_context->window->raw(), GLFW_KEY_A) == GLFW_PRESS)
	{
		_context->player->rotate_clockwise(delta);
	}
	if (glfwGetKey(_context->window->raw(), GLFW_KEY_D) == GLFW_PRESS)
	{
		_context->player->rotate_counter_clockwise(delta);
	}
	_context->window->pollEvents();*/
}

void Game::update(float delta)
{
}

void Game::draw()
{
	/*_context->player->draw();*/
	//sprite.draw();
}

const Window& Game::getWindow(void) const
{
	return _window;
}

/*Private Methods*/
bool Game::_initGLFW(void)
{
	if (glfwInit())
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW_VERSION_MAJOR);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_VERSION_MAJOR);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		return true;
	}
	else
	{
		return false;
	}
}

bool Game::_initWindow(void)
{
	bool success = _window.create(WINDOW_WIDTH, WINDOW_HEIGHT, "Asteroids");
	if (success)
	{
		//_window.setClearColour(Colours::Black);
		return true;
	}
	else
	{
		return false;
	}
}

bool Game::_initGL(void)
{
	glewExperimental = GL_TRUE;
	if (glewInit() == GLEW_OK)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		return true;
	}
	else
	{
		return false;
	}
}

bool Game::_initResourceCache(void)
{
	/*Factory Registration*/
	_cache.registerFactory(new ImageResourceFactory);
	_cache.registerFactory(new ShaderResourceFactory);

	/*Image Resources*/
	_cache.preload(HashString("Resource/Images/player.png"));
	_cache.preload(HashString("Resource/Images/laser.png"));
	_cache.preload(HashString("Resource/Images/asteroid.png"));
	_cache.preload(HashString("Resource/Images/space_background.png"));
	//_cache.preload(HashString"Resource/Images/background.png");

	/*Sound Resources*/
	//CREATE THEM!

	/*Shader Resources*/
	_cache.preload(HashString("Resource/Shaders/vertex.vert"));
	_cache.preload(HashString("Resource/Shaders/fragment.frag"));
	
	return true;
}

bool Game::_initShader(void)
{
	ShaderResource* vertex = _cache.load<ShaderResource>(HashString("Resource/Shaders/vertex.vert"));
	ShaderResource* fragment = _cache.load<ShaderResource>(HashString("Resource/Shaders/fragment.frag"));
	_shader.compile(vertex->getSource(), fragment->getSource());
	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
	_shader.bind();
	_shader.setInteger("image", 0);
	_shader.setMatrix4("projection", projection);

	return true;
}

void Game::_terminate(const std::string& source)
{
	std::cout << "Game terminated due to \"" << source << "\" failing to load." << std::endl;
	system("PAUSE");
	system(0);
}