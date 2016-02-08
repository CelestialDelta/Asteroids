#include "..\Public\entity_def.h"
#include "..\Public\world.h"

/*
=====================================

ASTEROID ENTITY

=====================================
*/

/*Public Methods*/
Asteroid::Asteroid(World* world, const Shader& shader, const Texture& texture, ID id)
	: Drawable(shader, texture, EntityT::ASTEROID), Moveable(), Boundable(), Destroyable(ASTEROID_DURATION), 
	_world(world), _ID(id)
{
	switch (id)
	{
	case SMALL:
		_createSmall();
		break;
	case MEDIUM:
		_createMedium();
		break;
	case LARGE:
		_createLarge();
		break;
	}
}

void Asteroid::draw(void)
{
	Drawable::draw();
}

void Asteroid::handle(float delta)
{
}

void Asteroid::update(float delta)
{
	move(delta);
	float count = getCounter();
	if (count >= getDuration())
	{
		destroy();
	}
	else
	{
		setCounter(count + delta * 3.0f);
		std::cout << "Count: " << getCounter() << std::endl;
	}
}


void Asteroid::move(float delta)
{
	checkBorder();
	float xPos = getXPosition();
	float yPos = getYPosition();
	xPos += (getCurrentHoriztonalVelocity() * getHorizontalRotationManip() * delta);
	yPos += (-getCurrentVerticalVelocity() * getVerticalRotationManip() * delta);
	setPosition(xPos, yPos);
}

void Asteroid::checkBorder(void)
{
	float xPos = getXPosition();
	float yPos = getYPosition();
	float xSize = getXSize();
	float ySize = getYSize();

	if (xPos <= _world->getBounds().left - xSize)
	{
		setPosition(_world->getBounds().right + xSize - BORDER_WARP_OFFSET, yPos);
	}
	if (xPos >= _world->getBounds().right + xSize)
	{
		setPosition(_world->getBounds().left - xSize + BORDER_WARP_OFFSET, yPos);
	}
	if (yPos <= _world->getBounds().top - ySize)
	{
		setPosition(xPos, _world->getBounds().bottom + ySize - BORDER_WARP_OFFSET);
	}
	if (yPos >= _world->getBounds().bottom + ySize)
	{
		setPosition(xPos, _world->getBounds().top - ySize + BORDER_WARP_OFFSET);
	}
}

void Asteroid::destroy(void)
{
	_world->remove(this);
}

void Asteroid::undestroy(void)
{
}

World* Asteroid::getWorld(void) const
{
	return _world;
}

/*Private Methods*/
void Asteroid::_createSmall(void)
{
	setSize(50, 50);
	setPosition(100, 100);
	setCurrentVelocity(300, 300);
	setMaximumVelocity(300, 300);
	setRotationManip(glm::vec2(std::sin(getRotation()), 
		std::cos(getRotation())));
}

void Asteroid::_createMedium(void)
{
	setSize(100, 100);
	setPosition(200, 200);
	setCurrentVelocity(10, 10);
	setMaximumVelocity(10, 10);
	setRotationManip(glm::vec2(std::sin(getRotation()), 
		std::cos(getRotation())));
}

void Asteroid::_createLarge(void)
{
	setSize(200, 200);
	setPosition(300, 300);
	setCurrentVelocity(8, 8);
	setMaximumVelocity(8, 8);
	setRotationManip(glm::vec2(std::sin(getRotation()), 
		std::cos(getRotation())));
}

Asteroid::ID intToID(int num)
{
	switch (num)
	{
	case Asteroid::SMALL:
		return Asteroid::SMALL;
	case Asteroid::MEDIUM:
		return Asteroid::MEDIUM;
	case Asteroid::LARGE:
		return Asteroid::LARGE;
	default:
		return Asteroid::NONE;
	}
}

/*
==================

ASTEROID GENERATOR

==================
*/

AsteroidGenerator::AsteroidGenerator(void)
	: _world(nullptr), _shader(), _asteroidTexture()
{
}

AsteroidGenerator::AsteroidGenerator(const Shader& shader, const Texture& texture)
	: _world(nullptr), _shader(shader), _asteroidTexture(texture)
{
}

Asteroid* AsteroidGenerator::generate(float delta)
{
	static float delay = 0.0f;
	if (delay + delta * 6 >= ASTEROID_SPAWN_DELAY)
	{
		delay = 0.0f;
		std::srand(time(nullptr));
		Asteroid::ID id = intToID(rand() % 5);
		if (id != Asteroid::NONE)
		{
			Asteroid* asteroid = new Asteroid(_world, _shader, _asteroidTexture, id);
			return asteroid;
		}
	}
	delay += delta * 6;
	return nullptr;
}

void AsteroidGenerator::setWorld(World* world)
{
	_world = world;
}

void AsteroidGenerator::setShader(const Shader& shader)
{
	_shader = shader;
}

void AsteroidGenerator::setAsteroidTexture(const Texture& texture)
{
	_asteroidTexture = texture;
}

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

PlayerState::PlayerState(StateStack* stack, Player* player, Type type)
	: State(stack), _player(player), _type(type)
{
}

PlayerState::Type PlayerState::getType(void) const
{
	return _type;
}

/*
=========================

PLAYER STATE ACCELERATING

=========================
*/

PlayerStateAccelerating::PlayerStateAccelerating(StateStack* stack, Player* player)
	: PlayerState(stack, player, ACCELERATING)
{
}

void PlayerStateAccelerating::draw(void)
{
	_player->draw();
}

void PlayerStateAccelerating::handle(float delta)
{
	if (glfwGetKey(_player->getWindow()->getRawWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{
		if (!_player->checkDirection())
		{
			_player->setRotation(_player->getDirection());
			_player->setHorizontalRotationManip(std::sin(_player->getRotation()));
			_player->setVerticalRotationManip(std::cos(_player->getRotation()));
		}
		float xPos = _player->getXPosition();
		float yPos = _player->getYPosition();
		xPos += (_player->getCurrentHoriztonalVelocity() * _player->getHorizontalRotationManip() * delta);
		yPos += (-_player->getCurrentVerticalVelocity() * _player->getVerticalRotationManip() * delta);
		_player->setPosition(glm::vec2(xPos, yPos));
		if (_player->getCurrentVelocity() != _player->getMaximumVelocity())
		{
			float xCurrent = _player->getCurrentVelocity().x;
			float yCurrent = _player->getCurrentVelocity().y;
			xCurrent += std::log(xCurrent);
			yCurrent += std::log(yCurrent);
			_player->setCurrentVelocity(glm::vec2(xCurrent, yCurrent));
		}
	}
	if (glfwGetKey(_player->getWindow()->getRawWindow(), GLFW_KEY_W) != GLFW_PRESS)
	{
		PlayerState* state = (PlayerState*)_stack->peek();
		if (state->getType() != DRIFTING)
		{
			_stack->swap(new PlayerStateDrifting(_stack, _player));
		}
	}
	if (glfwGetKey(_player->getWindow()->getRawWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		_player->rotateCounterClockwise(delta);
	}
	if (glfwGetKey(_player->getWindow()->getRawWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		_player->rotateClockwise(delta);
	}
	if (glfwGetKey(_player->getWindow()->getRawWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		_player->shoot(delta);
	}
}

void PlayerStateAccelerating::update(float delta)
{
	_player->update(delta);
}

/*
=====================

PLAYER STATE DRIFTING

=====================
*/

PlayerStateDrifting::PlayerStateDrifting(StateStack* stack, Player* player)
	: PlayerState(stack, player, DRIFTING)
{
}

void PlayerStateDrifting::draw(void)
{
	_player->draw();
}

void PlayerStateDrifting::handle(float delta)
{
	if (glfwGetKey(_player->getWindow()->getRawWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{	
		PlayerState* state = (PlayerState*)_stack->peek();
		if (state->getType() != ACCELERATING)
		{
			_stack->swap(new PlayerStateAccelerating(_stack, _player));
		}
	}
	if (glfwGetKey(_player->getWindow()->getRawWindow(), GLFW_KEY_W) != GLFW_PRESS)
	{
		if (!_player->checkDirection())
		{
			_player->setRotation(_player->getDirection());
			_player->setHorizontalRotationManip(std::sin(_player->getRotation()));
			_player->setVerticalRotationManip(std::cos(_player->getRotation()));
		}
		float xPos = _player->getXPosition();
		float yPos = _player->getYPosition();
		xPos += (_player->getCurrentHoriztonalVelocity() * _player->getHorizontalRotationManip() * delta);
		yPos += (-_player->getCurrentVerticalVelocity() * _player->getVerticalRotationManip() * delta);
		_player->setPosition(glm::vec2(xPos, yPos));
		if (_player->getCurrentVelocity() != ZERO_VELOCITY)
		{
			float xCurrent = _player->getCurrentVelocity().x;
			float yCurrent = _player->getCurrentVelocity().y;
			xCurrent -= std::log10(xCurrent);
			yCurrent -= std::log10(yCurrent);
			_player->setCurrentVelocity(glm::vec2(xCurrent, yCurrent));
		}
		else
		{
			PlayerState* state = (PlayerState*)_stack->peek();
			if (state->getType() != STATIONARY)
			{
				_stack->push(new PlayerStateStationary(_stack, _player));
			}
		}
	}
	if (glfwGetKey(_player->getWindow()->getRawWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		_player->rotateCounterClockwise(delta);
	}
	if (glfwGetKey(_player->getWindow()->getRawWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		_player->rotateClockwise(delta);
	}
	if (glfwGetKey(_player->getWindow()->getRawWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		_player->shoot(delta);
	}
}

void PlayerStateDrifting::update(float delta)
{
	_player->update(delta);
}

/*
=======================

PLAYER STATE STATIONARY

=======================
*/

PlayerStateStationary::PlayerStateStationary(StateStack* stack, Player* player)
	: PlayerState(stack, player, STATIONARY)
{
}

void PlayerStateStationary::draw(void)
{
	_player->draw();
}

void PlayerStateStationary::handle(float delta)
{
	if (!_player->checkDirection())
	{
		_player->setRotation(_player->getDirection());
		_player->setHorizontalRotationManip(std::sin(_player->getRotation()));
		_player->setVerticalRotationManip(std::cos(_player->getRotation()));
	}
	if (glfwGetKey(_player->getWindow()->getRawWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{
		PlayerState* state = (PlayerState*)_stack->peek();
		if (state->getType() != ACCELERATING)
		{
			_stack->swap(new PlayerStateAccelerating(_stack, _player));
		}
	}
	if (glfwGetKey(_player->getWindow()->getRawWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		_player->rotateCounterClockwise(delta);
		_player->setRotation(_player->getDirection());
	}
	if (glfwGetKey(_player->getWindow()->getRawWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		_player->rotateClockwise(delta);
		_player->setRotation(_player->getDirection());
	}
	if (glfwGetKey(_player->getWindow()->getRawWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		_player->shoot(delta);
	}
}

void PlayerStateStationary::update(float delta)
{
	_player->update(delta);
}

/*
==================

PLAYER STATE STACK

==================
*/

PlayerStateStack::PlayerStateStack(Player* player)
	: StateStack(), _player(player)
{
}

PlayerStateStack::~PlayerStateStack(void)
{
}

void PlayerStateStack::push(State* state)
{
	_states.push_back(state);
}

void PlayerStateStack::pop(void)
{
	_states.pop_back();
}

State* PlayerStateStack::peek(void)
{
	return (PlayerState*)_states.back();
}

void PlayerStateStack::swap(State* state)
{
	if (peek())
	{
		pop();
	}
	push(state);
}

/*
==========

PROJECTILE

==========
*/

Projectile::Projectile(Player* player, const Shader& shader, const Texture& texture)
	: Drawable(shader, texture, EntityT::PROJECTILE), Moveable(), Destroyable(PROJECTILE_DURATION), Boundable(), _player(player)
{
	setSize(PROJECTILE_SIZE);
	setPosition(player->getPosition());
	setRotation(player->getDirection());
	setRotationManip(player->getRotationManip());
	setMaximumVelocity(PROJECTILE_VELOCITY);
	setCurrentVelocity(PROJECTILE_VELOCITY);
}

void Projectile::draw(void)
{
	Drawable::draw();
}

void Projectile::handle(float delta)
{
}

void Projectile::update(float delta)
{
	move(delta);
	float count = getCounter();
	if (count >= getDuration())
	{
		destroy();
	}
	else
	{
		setCounter(count + delta * 15.0f);
	}
}

void Projectile::move(float delta)
{
	checkBorder();
	float xPos = getXPosition();
	float yPos = getYPosition();
	xPos += (getCurrentHoriztonalVelocity() * getHorizontalRotationManip() * delta);
	yPos += (-getCurrentVerticalVelocity() * getVerticalRotationManip() * delta);
	setPosition(xPos, yPos);
}

void Projectile::checkBorder(void)
{
	float xPos = getXPosition();
	float yPos = getYPosition();
	float xSize = getXSize();
	float ySize = getYSize();

	if (xPos <= _player->getWorld()->getBounds().left - xSize)
	{
		setPosition(_player->getWorld()->getBounds().right + xSize - BORDER_WARP_OFFSET, yPos);
	}
	if (xPos >= _player->getWorld()->getBounds().right + xSize)
	{
		setPosition(_player->getWorld()->getBounds().left - xSize + BORDER_WARP_OFFSET, yPos);
	}
	if (yPos <= _player->getWorld()->getBounds().top - ySize)
	{
		setPosition(xPos, _player->getWorld()->getBounds().bottom + ySize - BORDER_WARP_OFFSET);
	}
	if (yPos >= _player->getWorld()->getBounds().bottom + ySize)
	{
		setPosition(xPos, _player->getWorld()->getBounds().top - ySize + BORDER_WARP_OFFSET);
	}
}

void Projectile::destroy(void)
{
	_player->deleteProjectile(this);
}

void Projectile::undestroy(void)
{
}

/*
======

PLAYER

======
*/

Player::Player(Window* window, World* world, const Shader& shader, const Texture& texture, const Texture& projectile)
	: Drawable(shader, texture, EntityT::PLAYER), Moveable(), Destroyable(), Boundable(), 
	_window(window), _world(world), _states(this), _projectiles(), _projectileTexture(projectile)
{
	setPosition(MID_WINDOW_WIDTH, MID_WINDOW_HEIGHT);
	setSize(50, 50);
	setRotation(0);
	setRotationalSpeed(5);
	setCurrentVelocity(40, 40);
	setRotationManip(glm::vec2(std::sin(getRotation()), 
		std::cos(getRotation())));
	_states.push(new PlayerStateStationary(&_states, this));
}

void Player::draw(void)
{
	Drawable::draw();
	for (unsigned int i = 0; i < _projectiles.size(); i++)
	{
		_projectiles.at(i)->draw();
	}
}

void Player::handle(float delta)
{
	move(delta);
}

void Player::update(float delta)
{
	for (unsigned int i = 0; i < _projectiles.size(); i++)
	{
		_projectiles.at(i)->update(delta);
	}
}

void Player::move(float delta)
{
	checkBorder();
	_states.peek()->handle(delta);
	_states.peek()->update(delta);
	_states.peek()->draw();
}

void Player::checkBorder(void)
{
	float xPos = getXPosition();
	float yPos = getYPosition();

	float xSize = getXSize();
	float ySize = getYSize();
	if (xPos <= _world->getBounds().left - xSize)
	{
		setPosition(_world->getBounds().right + xSize - BORDER_WARP_OFFSET, yPos);
	}
	if (xPos >= _world->getBounds().right + xSize)
	{
		setPosition(_world->getBounds().left - xSize + BORDER_WARP_OFFSET, yPos);
	}
	if (yPos <= _world->getBounds().top - ySize)
	{
		setPosition(xPos, _world->getBounds().bottom + ySize - BORDER_WARP_OFFSET);
	}
	if (yPos >= _world->getBounds().bottom + ySize)
	{
		setPosition(xPos, _world->getBounds().top - ySize + BORDER_WARP_OFFSET);
	}
}

void Player::destroy(void)
{
}

void Player::undestroy(void)
{
}

void Player::shoot(float delta)
{
	static float count = 0.0f;
	if (count + delta * 10 >= PROJECTILE_DELAY)
	{
		_projectiles.push_back(new Projectile(this, _shader, _projectileTexture));
		count = 0.0f;
	}
		count += delta * 10;
}

void Player::deleteProjectile(Projectile* projectile)
{
	ProjectileItr found = std::find(_projectiles.begin(), _projectiles.end(), projectile);
	if (found != _projectiles.end())
	{
		delete (*found);
		_projectiles.erase(found);
	}
}

void Player::setProjectileTexture(const Texture& projectile)
{
	_projectileTexture = projectile;
}

Window* Player::getWindow(void) const
{
	return _window;
}

World* Player::getWorld(void) const
{
	return _world;
}

const Texture& Player::getProjectileTexture(void) const
{
	return _projectileTexture;
}

bool Player::hasProjectiles(void) const
{
	return !_projectiles.size();
}