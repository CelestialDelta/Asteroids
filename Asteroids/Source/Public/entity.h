#pragma once

/*OpenGL Libraries*/
#include <GL\glew.h>
#include <glm\glm.hpp>

/*Standard Library*/
#include <vector>
#include <algorithm>
#include <math.h>
#include <type_traits>
#include <vector>

/*Custom Library*/
#include "texture.h"
#include "sprite.h"

class World;

enum class EntityT
{
	PLAYER, ASTEROID, PROJECTILE
};

/*
=====================================

BOUNDABLE

=====================================
*/

class Boundable
{
public:
	Boundable					(void);

	void setBounds				(glm::vec2 bounds);
	void setBounds				(float xBound, float yBound);
	void setXBound				(float xBound);
	void setYBound				(float yBound);
	void setOrigin				(glm::vec2 origin);
	void setOrigin				(float xOrigin, float yOrigin);
	void setXOrigin				(float xOrigin);
	void setYOrigin				(float yOrigin);

	glm::vec2 getBounds			(void) const;
	float getXBound				(void) const;
	float getYBound				(void) const;
	glm::vec2 getOrigin			(void) const;
	float getXOrigin			(void) const;
	float getYOrigin			(void) const;
protected:
	glm::vec2	_bounds;
	glm::vec2	_origin;
};

/*
=====================================

DRAWABLE

=====================================
*/

class Drawable
{
public:
	Drawable						(const Shader& shader, const Texture& texture, EntityT type);

	virtual void draw				(void);
	virtual void handle				(float delta) = 0;
	virtual void update				(float delta) = 0;

	void setShader					(const Shader& shader);
	void setTexture					(const Texture& texture);
	void setPosition				(glm::vec2 size);
	void setPosition				(float XPos, float yPos);
	void setXPositon				(float xPos);
	void setYPosition				(float yPos);
	void setRotation				(float degree);
	void setSize					(glm::vec2 size);
	void setSize					(float xSize, float ySize);
	void setXSize					(float xSize);
	void setYSize					(float ySize);
	void setColour					(float red, float green, float blue, float alpha = 1.0f);
	void setColour					(Colour colour);

	const Shader& getShader			(void) const;
	const Texture& getTexture		(void) const;
	glm::vec2 getPosition			(void) const;
	float getXPosition				(void) const;
	float getYPosition				(void) const;
	float getRotation				(void) const;
	glm::vec2 getSize				(void) const;
	float getXSize					(void) const;
	float getYSize					(void) const;
	Colour getColour				(void) const;
	EntityT getType					(void) const;
protected:
	Shader			_shader;
	Texture			_texture;
	glm::vec2		_position;
	float			_rotation;
	glm::vec2		_size;
	Colour			_colour;
	glm::mat4		_model;
	GLuint			_quadVAO;
	EntityT			_type;
private:
	void _init();
};

/*
=====================================

MOVEABLE

=====================================
*/

#define MAXIMUM_VELOCITY	550
#define ZERO_VELOCITY		glm::vec2(0, 0)

class Moveable
{
public:
	Moveable									(void);

	virtual void move(float delta) = 0;

	virtual void checkBorder					(void) = 0;
	bool checkXVelocity							(void) const;
	bool checkYVelocity							(void) const;
	bool checkDirection							(void) const;

	void rotateClockwise						(float delta);
	void rotateCounterClockwise					(float delta);

	void setMaximumVelocity						(glm::vec2 maxVelocity);
	void setMaximumVelocity						(float xMax, float yMax);
	void setCurrentVelocity						(glm::vec2 currVelocity);
	void setCurrentVelocity						(float xCur, float yCur);
	void setMaximumHorizontalVelocity			(float horizontal);
	void setMaximumVerticalVelocity				(float vertical);
	void setCurrentHorizontalVelocity			(float horizontal);
	void setCurrentVerticalVelocity				(float vertical);
	void setRotationManip						(glm::vec2 manip);
	void setHorizontalRotationManip				(float horiztonal);
	void setVerticalRotationManip				(float vertical);
	void setDirection							(float dir);
	void setRotationalSpeed						(float fSpeed);

	glm::vec2 getMaximumVelocity				(void) const;
	glm::vec2 getCurrentVelocity				(void) const;
	float getMaximumHorizontalVelocity			(void) const;
	float getMaximumVerticalVelocity			(void) const;
	float getCurrentHoriztonalVelocity			(void) const;
	float getCurrentVerticalVelocity			(void) const;
	glm::vec2 getRotationManip					(void) const;
	float getHorizontalRotationManip			(void) const;
	float getVerticalRotationManip				(void) const;
	float getDirection							(void) const;
	float getRotationalSpeed					(void) const;
protected:
	glm::vec2	_maximumVelocity;
	glm::vec2	_currentVelocity;
	float		_direction;
	float		_rotationalSpeed;
	glm::vec2	_rotationManip;
};

/*
/*
=====================================

DESTROYABLE

=====================================
*/

//Perhaps implement "Undestoryable" 
//which holds a pointer to a cache the keeps destoryed items information?

class Destroyable
{
public:
	Destroyable					(void);
	Destroyable					(float duration);

	virtual void destroy		(void) = 0;
	virtual void undestroy		(void) = 0;

	void canDestory				(void);
	void cannotDestory			(void);
	void setDuration			(float duration);
	void setCounter				(float count);

	bool getDestoryStatus		(void) const;
	float getDuration			(void) const;
	float getCounter			(void) const;
protected:
	bool		_canDestory;
	float		_duration;
	float		_counter;
};

/*
=====================================

ENTITY MANAGER

=====================================
*/

class EntityManager
{
public:
	typedef std::vector<Drawable*>					Manager;
	typedef std::vector<Drawable*>::iterator		iterator;

	EntityManager				(void);
	~EntityManager				(void);

	void add					(Drawable* entity);
	Drawable* get				(unsigned int index);
	void remove					(Drawable* entity);
	iterator find				(const Drawable* entity);
	void clear					(void);

	iterator begin				(void);
	iterator end				(void);

	unsigned int getSize		(void) const;
private:
	Manager _entities;
};