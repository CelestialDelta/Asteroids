#include "..\Public\world.h"

/*
=====================================

WORLD

=====================================
*/

World::Bounds::Bounds(void)
	: bottom(WINDOW_HEIGHT), right(WINDOW_WIDTH), top(0), left(0)
{
}

World::World(void)
	: _entManager(), _background(), _bounds(), _generator(), _asteroidCount(0)
{
}

World::World(const Shader& shader, const Texture& background, const AsteroidGenerator& generator)
	: _entManager(), _background(background), _bounds(), _generator(generator), _asteroidCount(0)
{
	_background.setShader(shader);
	_background.setPosition(0, 0);
	_background.setSize(800, 600);
	_generator.setWorld(this);
}

void World::draw(void)
{
	_background.draw();
	for (EntityManager::iterator itr = _entManager.begin(); itr != _entManager.end(); itr++)
	{
		(*itr)->draw();
	}
}

void World::update(float delta)
{
	for (EntityManager::iterator itr = _entManager.begin(); itr != _entManager.end(); itr++)
	{
		(*itr)->update(delta);
	}
}

void World::handle(float delta)
{
	Asteroid* asteroid = _generator.generate(delta);
	if (asteroid)
	{
		if (_asteroidCount < MAX_ASTEROID_BUFFER)
		{
			_asteroidCount++;
			_entManager.add(asteroid);
		}
	}
	for (EntityManager::iterator itr = _entManager.begin(); itr != _entManager.end(); itr++)
	{
		(*itr)->handle(delta);
	}
}

void World::include(Drawable* entity)
{
	_entManager.add(entity);
}

void World::remove(Drawable* entity)
{
	if (entity->getType() == EntityT::ASTEROID)
	{
		_asteroidCount--;
		std::cout << "Count down" << std::endl;
	}
	_entManager.remove(entity);
}

EntityManager::iterator World::find(const Drawable* entity)
{
	return _entManager.find(entity);
}

EntityManager World::getEntityManager(void) const
{
	return _entManager;
}

World::Bounds World::getBounds(void) const
{
	return _bounds;
}