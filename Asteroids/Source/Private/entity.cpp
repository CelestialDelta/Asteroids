#include "..\Public\entity.h"


/*
=====================================

BOUNDABLE

=====================================
*/

Boundable::Boundable(void)
	: _bounds(), _origin()
{
}

void Boundable::setBounds(glm::vec2 bounds)
{
	_bounds = bounds;
	_origin = _bounds * 0.5f;
}

void Boundable::setBounds(float xBound, float yBound)
{
	_bounds = glm::vec2(xBound, yBound);
	_origin = _bounds * 0.5f;
}

void Boundable::setXBound(float xBound)
{
	_bounds.x = xBound;
	_origin = _bounds * 0.5f;
}

void Boundable::setYBound(float yBound)
{
	_bounds.y = yBound;
	_origin = _bounds * 0.5f;
}

void Boundable::setOrigin(glm::vec2 origin)
{
	_origin = origin;
}

void Boundable::setOrigin(float xOrigin, float yOrigin)
{
	_origin = glm::vec2(xOrigin, yOrigin);
}

void Boundable::setXOrigin(float xOrigin)
{
	_origin.x = xOrigin;
}

void Boundable::setYOrigin(float yOrigin)
{
	_origin.y = yOrigin;
}

glm::vec2 Boundable::getBounds(void) const
{
	return _bounds;
}

float Boundable::getXBound(void) const
{
	return _bounds.x;
}

float Boundable::getYBound(void) const
{
	return _bounds.y;
}

glm::vec2 Boundable::getOrigin(void) const
{
	return _origin;
}

float Boundable::getXOrigin(void) const
{
	return _origin.x;
}

float Boundable::getYOrigin(void) const
{
	return _origin.y;
}

/*
=====================================

DRAWABLE

=====================================
*/

Drawable::Drawable(const Shader& shader, const Texture& texture, EntityT type)
	: _shader(shader), _texture(texture), _position(), _rotation(), _size(), _colour(Colours::White),
	_model(), _quadVAO(), _type(type)
{
	_init();
}

void Drawable::draw(void)
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

void Drawable::setShader(const Shader& shader)
{
	_shader = shader;
}

void Drawable::setTexture(const Texture& texture)
{
	_texture = texture;
}

void Drawable::setPosition(const glm::vec2 position)
{
	_position = position;
}

void Drawable::setPosition(float xPos, float yPos)
{
	_position = glm::vec2(xPos, yPos);
}


void Drawable::setXPositon(float xPos)
{
	_position.x = xPos;
}

void Drawable::setYPosition(float yPos)
{
	_position.y = yPos;
}

void Drawable::setRotation(float degree)
{
	_rotation = degree;
}

void Drawable::setSize(glm::vec2 size)
{
	_size = size;
}

void Drawable::setSize(float xSize, float ySize)
{
	_size = glm::vec2(xSize, ySize);
}

void Drawable::setXSize(float xSize)
{
	_size.x = xSize;
}

void Drawable::setYSize(float ySize)
{
	_size.y = ySize;
}

void Drawable::setColour(float red, float green, float blue, float alpha)
{
	_colour = Colour(red, green, blue, alpha);
}

void Drawable::setColour(Colour colour)
{
	_colour = colour;
}


const Shader& Drawable::getShader(void) const
{
	return _shader;
}

const Texture& Drawable::getTexture(void) const
{
	return _texture;
}

glm::vec2 Drawable::getPosition(void) const
{
	return _position;
}

float Drawable::getXPosition(void) const
{
	return _position.x;
}

float Drawable::getYPosition(void) const
{
	return _position.y;
}

float Drawable::getRotation(void) const
{
	return _rotation;
}

glm::vec2 Drawable::getSize(void) const
{
	return _size;
}

float Drawable::getXSize(void) const
{
	return _size.x;
}

float Drawable::getYSize(void) const
{
	return _size.y;
}

Colour Drawable::getColour(void) const
{
	return _colour;
}

EntityT Drawable::getType(void) const
{
	return _type;
}

void Drawable::_init(void)
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

/*
=====================================

MOVEABLE

=====================================
*/

Moveable::Moveable(void)
	: _maximumVelocity(MAXIMUM_VELOCITY), _currentVelocity(), _rotationManip()
{
}

bool Moveable::checkXVelocity(void) const
{
	return _currentVelocity.x <= _maximumVelocity.x;
}

bool Moveable::checkYVelocity(void) const
{
	return _currentVelocity.y <= _maximumVelocity.y;
}

bool Moveable::checkDirection(void) const
{
	static float prevDir = 0.0f;
	if (prevDir != _direction)
	{
		prevDir = _direction;
		return false;
	}
	else
	{
		return true;
	}
}

void Moveable::rotateClockwise(float delta)
{
	float direction = _direction;
	float rSpeed = _rotationalSpeed;
	setDirection(direction + rSpeed * delta);
}

void Moveable::rotateCounterClockwise(float delta)
{
	float direction = _direction;
	float rSpeed = _rotationalSpeed;
	setDirection(direction - rSpeed * delta);
}

void Moveable::setMaximumVelocity(glm::vec2 maximum)
{
	_maximumVelocity = maximum;
}

void Moveable::setMaximumVelocity(float xMax, float yMax)
{
	_maximumVelocity = glm::vec2(xMax, yMax);
}

void Moveable::setCurrentVelocity(glm::vec2 current)
{
	if (current.x <= _maximumVelocity.x && current.y <= _maximumVelocity.y)
	{
		_currentVelocity = current;
	}
}

void Moveable::setCurrentVelocity(float xCur, float yCur)
{
	if (xCur <= getMaximumHorizontalVelocity() &&
		yCur <= getMaximumVerticalVelocity())
	{
		_currentVelocity = glm::vec2(xCur, yCur);
	}
}

void Moveable::setMaximumHorizontalVelocity(float horizontal)
{
	_maximumVelocity.x = horizontal;
}

void Moveable::setMaximumVerticalVelocity(float vertical)
{
	_maximumVelocity.y = vertical;
}

void Moveable::setCurrentHorizontalVelocity(float horizontal)
{
	if (horizontal <= getMaximumHorizontalVelocity())
	{
		_currentVelocity.x = horizontal;
	}
}

void Moveable::setCurrentVerticalVelocity(float vertical)
{
	if (vertical <= getMaximumVerticalVelocity())
	{
		_currentVelocity.x = vertical;
	}
}

void Moveable::setRotationManip(glm::vec2 manip)
{
	_rotationManip = manip;
}

void Moveable::setHorizontalRotationManip(float horizontal)
{
	_rotationManip.x = horizontal;
}

void Moveable::setVerticalRotationManip(float vertical)
{
	_rotationManip.y = vertical;
}

void Moveable::setDirection(float dir)
{
	_direction = dir;
}

void Moveable::setRotationalSpeed(float fSpeed)
{
	_rotationalSpeed = fSpeed;
}

glm::vec2 Moveable::getMaximumVelocity(void) const
{
	return _maximumVelocity;
}

glm::vec2 Moveable::getCurrentVelocity(void) const
{
	return _currentVelocity;
}

float Moveable::getMaximumHorizontalVelocity(void) const
{
	return _maximumVelocity.x;
}

float Moveable::getMaximumVerticalVelocity(void) const
{
	return _maximumVelocity.y;
}

float Moveable::getCurrentHoriztonalVelocity(void) const
{
	return _currentVelocity.x;
}

float Moveable::getCurrentVerticalVelocity(void) const
{
	return _currentVelocity.y;
}

glm::vec2 Moveable::getRotationManip(void) const
{
	return _rotationManip;
}

float Moveable::getHorizontalRotationManip(void) const
{
	return _rotationManip.x;
}

float Moveable::getVerticalRotationManip(void) const
{
	return _rotationManip.y;
}

float Moveable::getDirection(void) const
{
	return _direction;
}

float Moveable::getRotationalSpeed(void) const
{
	return _rotationalSpeed;
}

/*
===========

DESTORYABLE

===========
*/

Destroyable::Destroyable(void)
	: _canDestory(false), _duration(), _counter()
{
}

Destroyable::Destroyable(float duration)
	: _canDestory(false), _duration(duration), _counter()
{
}

void Destroyable::canDestory(void)
{
	_canDestory = true;
}

void Destroyable::cannotDestory(void)
{
	_canDestory = false;
}

void Destroyable::setDuration(float duration)
{
	_duration = duration;
}

void Destroyable::setCounter(float count)
{
	_counter = count;
}

bool Destroyable::getDestoryStatus(void) const
{
	return _canDestory;
}

float Destroyable::getDuration(void) const
{
	return _duration;
}

float Destroyable::getCounter(void) const
{
	return _counter;
}

/*
=====================================

ENTITY MANAGER

=====================================
*/

EntityManager::EntityManager(void)
	: _entities()
{
}

EntityManager::~EntityManager(void)
{
	clear();
}

void EntityManager::add(Drawable* ent)
{
	_entities.push_back(ent);
}

Drawable* EntityManager::get(unsigned int index)
{
	Drawable* ent = _entities.at(index);
	return ent;
}

void EntityManager::remove(Drawable* entity)
{
	iterator itr = find(entity);
	delete *itr;
	_entities.erase(itr);
}

EntityManager::iterator EntityManager::find(const Drawable* entity)
{
	iterator itr = std::find(_entities.begin(), _entities.end(), entity);
	return itr;
}

void EntityManager::clear(void)
{
	/*iterator delItr = _entities.begin();
	while (delItr != _entities.end())
	{
		delete *delItr;
		delItr = _entities.erase(delItr);
	}
	_entities.clear();*/
}

EntityManager::iterator EntityManager::begin(void)
{
	return _entities.begin();
}

EntityManager::iterator EntityManager::end(void)
{
	return _entities.end();
}

unsigned int EntityManager::getSize(void) const
{
	return _entities.size();
}