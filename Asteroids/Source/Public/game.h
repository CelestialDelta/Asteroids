#pragma once

/*OpenGL Libraries*/
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

/*Standard Library*/
#include <iostream>

/*Custom Library*/
#include "resource_cache.h"
#include "window.h"
#include "shader.h"
#include "entity_def.h"
#include "world.h"
#include "state_stack.h"

/*
=====================================

GAME

=====================================
*/

class GameState : public State
{
	GameState(StateStack* stack);
};

//class GameStateStack : public StateStack
//{
//};

class Game
{
public:
	Game							(void);

	void init						(void);
	void go							(void);

	void handle						(float delta);
	void update						(float delta);
	void draw						(void);

	const Window& getWindow			(void) const;

private:
	bool _initGLFW					(void);
	bool _initWindow				(void);
	bool _initGL					(void);
	bool _initResourceCache			(void);
	bool _initShader				(void);
	bool _initWorld					(void);
	void _terminate					(const std::string& source);

	ResourceCache		_cache;
	Window				_window;
	Shader				_shader;
	World				_world;
};