#pragma once

/*OpenGL Libraries*/
#include <GL\glew.h>
#include <glm\glm.hpp>

/*
=====================================

COLOUR

=====================================
*/

class Colour
{
public:
	Colour					(float red, float green, float blue, float alpha = 1.0f);

	struct Components
	{
		Components			(float r, float g, float b, float a);
		float red;
		float blue;
		float green;
		float alpha;
	};

	glm::vec3 toVector3f	(void);

	Components components;
};

/*
=====================================

COLOURS

=====================================
*/

namespace Colours
{
	static Colour White =			Colour(1.0f, 1.0f, 1.0f);
	static Colour Grey =			Colour(0.5f, 0.5f, 0.5f);
	static Colour Black =			Colour(0.0f, 0.0f, 0.0f);
	static Colour Red =				Colour(1.0f, 0.0f, 1.0f);
	static Colour Green =			Colour(0.0f, 1.0f, 0.0f);
	static Colour Blue =			Colour(0.0f, 0.0f, 1.0f);
	static Colour Transparent =		Colour(0.f, 0.f, 0.f, 0.f);
}