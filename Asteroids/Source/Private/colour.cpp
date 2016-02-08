#include "../Public/colour.h"

/*
=====================================

COLOUR

=====================================
*/

Colour::Colour(float red, float green, float blue, float alpha)
	: components(red, green, blue, alpha)
{
}

Colour::Components::Components(float r, float g, float b, float a)
	: red(r), green(g), blue(b), alpha(a)
{
}

glm::vec3 Colour::toVector3f()
{
	return glm::vec3(components.red, components.green, components.blue);
}