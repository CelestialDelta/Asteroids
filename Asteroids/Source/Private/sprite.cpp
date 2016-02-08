#include "..\Public\sprite.h"

/*
=====================================

SPRITE

=====================================
*/

/*Public Methods*/
Sprite::Sprite(void)
	: _shader(), _texture(Texture(new ImageResource("Resource/Images/default.png"))), 
	_position(0, 0), _size(0, 0), _colour(Colours::White), _rotation(0.0f), _model(), _quadVAO()
{
	_init();
}

Sprite::Sprite(const Texture& texture)
	: _shader(), _texture(texture), _position(0, 0), _size(0, 0), _colour(Colours::White),
	_rotation(0.0f), _model(), _quadVAO()
{
	_init();
}

void Sprite::draw()
{
	_shader.bind();
	_model = glm::mat4();
	_model = glm::translate(_model, glm::vec3(_position, 0.0f));
	_model = glm::translate(_model, glm::vec3(0.5f * _size.x, 0.5f * _size.y, 0.0f));
	_model = glm::rotate(_model, _rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	_model = glm::translate(_model, glm::vec3(-0.5f * _size.x, -0.5f * _size.y, 0.0f));
	_model = glm::scale(_model, glm::vec3(_size, 1.0f));

	_shader.setMatrix4("model", _model);
	_shader.setVector3f("spriteColor", _colour.toVector3f());

	glActiveTexture(GL_TEXTURE0);
	_texture.bind();
	glBindVertexArray(_quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void Sprite::setShader(const Shader& shader)
{
	_shader = shader;
}

void Sprite::setTexture(const Texture& texture)
{
	_texture = texture;
}

void Sprite::setPosition(glm::vec2 position)
{
	_position = position;
}

void Sprite::setPosition(float xPos, float yPos)
{
	_position = glm::vec2(xPos, yPos);
}

void Sprite::setXPosition(float xPos)
{
	_position.x = xPos;
}

void Sprite::setYPosition(float yPos)
{
	_position.y = yPos;
}

void Sprite::setSize(int width, int height)
{
	_size = glm::vec2(width, height);
}

void Sprite::setSize(glm::vec2 size)
{
	_size = size;
}

void Sprite::setColour(float red, float blue, float green, float alpha)
{
	_colour = Colour(red, blue, green, alpha);
}

void Sprite::setColour(Colour colour)
{
	_colour = colour;
}

void Sprite::setRotation(float degree)
{
	_rotation = degree;
}

const Shader& Sprite::getShader(void) const
{
	return _shader;
}

const Texture& Sprite::getTexture(void) const
{
	return _texture;
}

glm::vec2 Sprite::getPosition(void) const
{
	return _position;
}

float Sprite::getXPosition(void) const
{
	return _position.x;
}

float Sprite::getYPosition(void) const
{
	return _position.y;
}

glm::vec2 Sprite::getSize(void) const
{
	return _size;
}

Colour Sprite::getColour(void) const
{
	return _colour;
}

float Sprite::getRotation(void) const
{
	return _rotation;
}

/*Private Methods*/
void Sprite::_init(void)
{
	GLuint VBO;
	GLfloat vertices[] = 
	{
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &_quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(_quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}