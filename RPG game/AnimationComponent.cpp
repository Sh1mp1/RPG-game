#include "stdafx.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture)
	:sprite(sprite), texture(texture)
{
	this->lastAnimation = nullptr;
}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animations)
	{
		delete i.second;
	}
}

void AnimationComponent::addAnimation(const std::string key, sf::Vector2i startPos, int no_of_frames, sf::Vector2i size, float animationTimer)
{
	this->animations.emplace(key, new Animation(sprite, this->texture, startPos, no_of_frames, size, animationTimer));

	
}

//Functions
void AnimationComponent::play(const std::string key, const float& dt)
{
	if (this->lastAnimation != this->animations.at(key))
	{
		if (this->lastAnimation == nullptr)
		{
			this->lastAnimation = this->animations.at(key);
		}
		else
		{
			this->lastAnimation->reset();
			this->lastAnimation = this->animations.at(key);
		}
	}

	this->animations.at(key)->play(dt);
}
