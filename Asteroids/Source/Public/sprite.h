#pragma once

/*OpenGL Libraries*/
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

/*Custom Libraries*/
#include "texture.h"
#include "shader.h"
#include "colour.h"
#include "asteroid_def.h"

/*
=====================================

SPRITE

=====================================
*/

class Sprite
{
public:
	Sprite								(void);
	Sprite								(const Texture& texture);
	
	void draw							(void);

	void setShader						(const Shader& shader);
	void setTexture						(const Texture& texture);
	void setPosition					(glm::vec2 position);
	void setPosition					(float xPos, float yPos);
	void setXPosition					(float xPos);
	void setYPosition					(float yPos);
	void setSize						(int width, int height);
	void setSize						(glm::vec2 size);
	void setColour						(float red, float green, float blue, float alpha = 1.0f);
	void setColour						(Colour colour);
	void setRotation					(float degree);

	const Shader& getShader				(void) const;
	const Texture& getTexture			(void) const;
	glm::vec2 getPosition				(void) const;
	float getXPosition					(void) const;
	float getYPosition					(void) const;
	glm::vec2 getSize					(void) const;
	Colour getColour					(void) const;
	float getRotation					(void) const;
private:
	void _init							(void);

	Shader			_shader;
	Texture			_texture;
	glm::vec2		_position;
	glm::vec2		_size;
	Colour			_colour;
	float			_rotation;
	glm::mat4		_model;
	GLuint			_quadVAO;
};