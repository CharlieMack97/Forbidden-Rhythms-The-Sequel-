#include "Enemy.h"

Enemy::Enemy()
{
	Health = 100;
	setPosition(sf::Vector2f(300, 700));
	setSize(sf::Vector2f(32, 32));
	setScale(sf::Vector2f(3, 3));
    
	sprite.loadFromFile("gfx/lecturEH.png");
	setTexture(&sprite);

	for (int i = 0; i < 4; i++)
	{
		walk.addFrame(sf::IntRect(i * 32.f, 0.f, 32.f, 32.f));
	}

	currentAnimation = &walk;
	walk.setFrameSpeed(1.f / 10.f);
	moveSpeed = 0.05f;
    velocity = { 0,0 };

}
Enemy::~Enemy()
{

}

void Enemy::update(float dt)
{
    setCollisionBox(getPosition().x,getPosition().y, 96.f, 96.f);
	currentAnimation->animate(dt);
	setTextureRect(currentAnimation->getCurrentFrame());
	
}

void Enemy::move(const sf::Vector2f& playerPosition)
{
	// Calculate direction towards the player
	sf::Vector2f direction = playerPosition - getPosition();
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	// Normalize the direction vector (optional)
	if (length != 0) {
		direction /= length;
	}

	// Move the enemy towards the player
	setPosition(getPosition() + direction * moveSpeed);
}

void Enemy::render()
{
}
