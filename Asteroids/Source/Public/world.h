#pragma once

/*OpenGL Libraries*/
#include <GL\glew.h>

/*Custom Library*/
#include "..\Public\entity.h"
#include "..\Public\entity_def.h"

/*
=====================================

WORLD

=====================================
*/

#define BORDER_WARP_OFFSET 0.0001f

class World
{
public:
	struct Bounds
	{
		Bounds			(void);
		unsigned int	top;
		unsigned int	bottom;
		unsigned int	left;
		unsigned int	right;
	};
	World								(void);
	World								(const Shader& shader, const Texture& background, const AsteroidGenerator& generator);

	void draw							(void);
	void update							(float delta);
	void handle							(float delta);

	void include						(Drawable* entity);
	void remove							(Drawable* entity);
	EntityManager::iterator find		(const Drawable* entity);

	EntityManager getEntityManager(void) const;
	Bounds getBounds					(void) const;
	//void handle_collisions(void);
private:
	EntityManager		_entManager;
	Sprite				_background;
	Bounds				_bounds;
	AsteroidGenerator	_generator;
	unsigned int		_asteroidCount;
};