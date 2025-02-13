#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
	this->animationComponent = nullptr;
	this->movementComponent = nullptr;

}

void Entity::initSprite(sf::Texture& texture)
{
	this->sprite = sf::Sprite(texture);
}

void Entity::initMovementComponent(const float maxVelocity, const float minVelocity,  const float acceleration, const float deceleration, const bool canAccelerate)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, minVelocity, acceleration, deceleration, canAccelerate);
}

void Entity::initAnimationComponent(sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::initHitboxComponent(sf::Vector2f offset, sf::Vector2f size)
{
	this->hitboxComponent = new HitboxComponent(this->sprite, offset, size);
}

Entity::Entity(const float x, const float y, sf::Texture& texture)
{
	this->initVariables();
	
	this->initSprite(texture);

	this->sprite.setPosition(sf::Vector2f(x, y));
}

Entity::~Entity()
{	
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->hitboxComponent;
}

//Accessors
const sf::Vector2f Entity::getPosition() const
{
	return this->sprite.getPosition();
}

const sf::Vector2u Entity::getGridPosition(const unsigned grid_size) const
{
	if (this->hitboxComponent)
	{
		return sf::Vector2u(
			static_cast<unsigned>(this->hitboxComponent->getPosition().x) / grid_size,
			static_cast<unsigned>(this->hitboxComponent->getPosition().y) / grid_size
		);
	}

	return sf::Vector2u(
		static_cast<unsigned>(this->sprite.getPosition().x) / grid_size,
		static_cast<unsigned>(this->sprite.getPosition().y) / grid_size
	);
}

const sf::FloatRect Entity::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const sf::FloatRect Entity::getNextBounds() const
{
	if (this->movementComponent && this->hitboxComponent)
	{
		return this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity());
	}
	return sf::FloatRect();
}

const sf::FloatRect Entity::getNextBoundsX() const
{
	return this->hitboxComponent->getNextPositionX(this->movementComponent->getVelocity().x);
}

const sf::FloatRect Entity::getNextBoundsY() const
{
	return this->hitboxComponent->getNextPositionY(this->movementComponent->getVelocity().y);
}

const sf::RectangleShape& Entity::getHitbox() const
{
	return this->hitboxComponent->getHitbox();
}

//Modifiers
void Entity::setPosition(const sf::Vector2f& position)
{
	if (this->hitboxComponent != nullptr)
	{
		this->hitboxComponent->setPosition(position);
	}
	else
	{
		this->sprite.setPosition(position);
	}
}

void Entity::resetVelocityX()
{
	if (this->movementComponent)
	{
		this->movementComponent->resetVelocityX();
	}
}

void Entity::resetVelocityY()
{
	if (this->movementComponent)
	{
		this->movementComponent->resetVelocityY();
	}
}




//Component functions



//Functions
void Entity::move(const float& dt, sf::Vector2f dir)
{
	if (this->movementComponent)
		this->movementComponent->move(dt, dir, &this->sprite);	//Sets velocity from movement component	
}

void Entity::moveConstant(sf::Vector2f dir)
{
	this->movementComponent->moveConstant(dir, this->sprite);
}


void Entity::updateHitboxComponent()
{
	if (this->hitboxComponent)
	{
		this->hitboxComponent->update();
	}
}

void Entity::update(const float& dt)
{
	if (this->movementComponent != nullptr)
	{
		this->movementComponent->update(dt);
	}	
}

void Entity::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

