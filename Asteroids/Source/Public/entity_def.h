#pragma once

/*Standard Library*/
#include <time.h>
#include <stdlib.h>
#include <algorithm>

/*Custom Library*/
#include "entity.h"
#include "state_stack.h"
#include "window.h"

class Player;
/*
=====================================

ASTEROID ENTITY

=====================================
*/

/*
SMALL ASTEROID -	SIZE:	10x10 
					SPEED:	14x14

MEDIUM ASTEROID -	SIZE:	20x20
					SPEED:	10x10

LARGE ASTEROID -	SIZE:	40x40
					SPEED:	8x8
*/

/*
========

ASTEROID

========
*/

#define ASTEROID_DURATION	60.0f

class Asteroid 
	: public Drawable, public Moveable, 
	public Boundable, public Destroyable
{
public:
	enum ID
	{
		NONE, SMALL, MEDIUM, LARGE
	};

	Asteroid						(World* world, const Shader& shader, const Texture& texture, ID id);

	virtual void draw				(void) override;
	virtual void handle				(float delta) override;
	virtual void update				(float delta) override;
	virtual void move				(float delta) override;
	virtual void checkBorder		(void) override;
	virtual void destroy			(void) override;
	virtual void undestroy			(void) override;

	World* getWorld					(void) const;
protected:
	void _createSmall				(void);
	void _createMedium				(void);
	void _createLarge				(void);

	World*			_world;
	ID				_ID;
};

Asteroid::ID intToID(int num);

/*
==================

ASTEROID GENERATOR

==================
*/

#define MAX_ASTEROID_BUFFER		1//12
#define ASTEROID_SPAWN_DELAY	45.0f

class AsteroidGenerator
{
public:
	AsteroidGenerator				(void);
	AsteroidGenerator				(const Shader& shader, const Texture& texture);
	Asteroid* generate				(float delta);

	void setWorld					(World* world);
	void setShader					(const Shader& shader);
	void setAsteroidTexture			(const Texture& texture);
private:
	World*		_world;
	Shader		_shader;
	Texture		_asteroidTexture;
};

/*
=====================================

PLAYER SHIP

=====================================
*/

/*
============

PLAYER STATE

============
*/

class PlayerState 
	: public State
{
public:
	enum Type
	{
		ACCELERATING, DRIFTING, STATIONARY
	};
	PlayerState						(StateStack* stack, Player* player, Type type);

	virtual void draw				(void) = 0;
	virtual void handle				(float delta) = 0;
	virtual void update				(float delta) = 0;

	Type getType					(void) const;
protected:
	Player*		_player;
	Type		_type;
};

/*
=========================

PLAYER STATE ACCELERATING

=========================
*/

class PlayerStateAccelerating 
	: public PlayerState
{
public:
	PlayerStateAccelerating				(StateStack* stack, Player* player);

	virtual void draw					(void) override;
	virtual void handle					(float delta) override;
	virtual void update					(float delta) override;
};

/*
=====================

PLAYER STATE DRIFTING

=====================
*/

class PlayerStateDrifting 
	: public PlayerState
{
public:
	PlayerStateDrifting				(StateStack* stack, Player* player);

	virtual void draw				(void) override;
	virtual void handle				(float delta) override;
	virtual void update				(float delta) override;
};

/*
=======================

PLAYER STATE STATIONARY

=======================
*/

class PlayerStateStationary 
	: public PlayerState
{
public:
	PlayerStateStationary			(StateStack* stack, Player* player);

	virtual void draw				(void) override;
	virtual void handle				(float delta) override;
	virtual void update				(float delta) override;
};

/*
==================

PLAYER STATE STACK

==================
*/

class PlayerStateStack 
	: public StateStack
{
public:
	PlayerStateStack					(Player* player);
	virtual ~PlayerStateStack			(void) override;

	virtual void push					(State* state) override;
	virtual void pop					(void) override;
	virtual State* peek					(void) override;
	virtual void swap					(State* state) override;
protected:
	Player*	_player;
};

/*
==========

PROJECTILE

==========
*/

#define PROJECTILE_SIZE				glm::vec2(50, 50)
#define PROJECTILE_VELOCITY			glm::vec2(500, 500)
#define PROJECTILE_DURATION			30.0f
#define RESET_DURATION				0.0f

class Projectile 
	: public Drawable, public Moveable, 
	public Boundable, public Destroyable
{
public:
	Projectile						(Player* player, const Shader& shader, const Texture& texture);
	virtual void draw				(void) override;
	virtual void handle				(float delta) override;
	virtual void update				(float delta) override;
	virtual void move				(float delta) override;
	virtual void checkBorder		(void) override;
	virtual void destroy			(void) override;
	virtual void undestroy			(void) override;
private:
	Player*		_player;
};

/*
======

PLAYER

======
*/

#define PROJECTILE_DELAY	3.0f

class Player 
	: public Drawable, public Moveable, 
	public Boundable, public Destroyable
{
public:
	typedef std::vector<Projectile*>				Projectiles;
	typedef std::vector<Projectile*>::iterator		ProjectileItr;

	Player										(Window* window, World* world, const Shader& shader, 
													const Texture& texture, const Texture& projectile);

	virtual void draw							(void) override;
	virtual void handle							(float delta) override;
	virtual void update							(float delta) override;
	virtual void move							(float delta) override;
	virtual void checkBorder					(void) override;
	virtual void destroy						(void) override;
	virtual void undestroy						(void) override;

	void shoot									(float delta);
	void deleteProjectile						(Projectile* projectile);

	void setProjectileTexture					(const Texture& laserText);

	Window* getWindow							(void) const;
	World* getWorld								(void) const;
	const Texture& getProjectileTexture			(void) const;

	bool hasProjectiles							(void) const;
private:
	Window*					_window;
	World*					_world;
	PlayerStateStack		_states;
	Texture					_projectileTexture;
	Projectiles				_projectiles;
};