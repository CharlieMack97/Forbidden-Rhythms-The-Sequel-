#include "PlayerSurvival.h"
#include <iostream>
PlayerSurvival::PlayerSurvival()
{
	health = 100;
	setPosition(sf::Vector2f(100, 100));
	setSize(sf::Vector2f(100, 100));

	dino.loadFromFile("gfx/dinoVita.png");
	
	
	setTexture(&dino); // set that texture to this object.

	// dino texture is 24x24px. Frames for walk are 4 - 9, inclusive.
	for (int i = 4; i < 10; ++i)
	{
		walk.addFrame(sf::IntRect(i * 24.f, 0.f, 24.f, 24.f));
	}
	for (int i = 0; i < 4; ++i)
	{
		kick.addFrame(sf::IntRect(i * 24.f + 240.f, 0.f, 24.f, 24.f));
	}
	damaged.addFrame(sf::IntRect(0, 0, 24, 24));
	damaged.addFrame(sf::IntRect(15 * 24, 0, 24, 24));
	damaged.setFrameSpeed(1.f / 4.f);
	currentAnimation = &walk;
	walk.setFrameSpeed(1.f / 10.f);
	//kick.setLooping(false);

	float bulletSpeed = 50.f;
	horizontalVel = 0.f;
	verticalVel = 0.f;
	velocity = { 0,0 };
	directionFacing = sf::Vector2f(1.0f, 0.0f);
}

PlayerSurvival::~PlayerSurvival()
{
}

void PlayerSurvival::handleInput(float dt)
{

	if(playerNum == 1)
	{
		if (input->isKeyDown(sf::Keyboard::A))
		{
			horizontalVel  = -175;
			setFlipped(true);
			directionFacing = sf::Vector2f(-1.0f, 0.0f);
			moving = true;
		}
		if (input->isKeyDown(sf::Keyboard::W) && isGrounded == true)
		{
			//jumpTime = 15.f;
			verticalVel = -350;
		}
		if (input->isKeyDown(sf::Keyboard::D))
		{
			horizontalVel = 175;
			setFlipped(false);
			directionFacing = sf::Vector2f(1.0f, 0.0f);
			moving = true;
		}
		if (!input->isKeyDown(sf::Keyboard::A) && !input->isKeyDown(sf::Keyboard::D))
		{
			horizontalVel = 0;
			moving = false;
		}
		if (input->isKeyDown(sf::Keyboard::Space) && canAttack)
		{
			Attacking = true;
			currentAnimation = &kick;
		}
		else
		{
			Attacking = false;
			currentAnimation = &walk;
		}
	}
	else if (playerNum == 2)
	{
		if (input->isKeyDown(sf::Keyboard::Left))
		{
			horizontalVel = -175;
			setFlipped(true);
			directionFacing = sf::Vector2f(-1.0f, 0.0f);
			moving = true;
		}
		if (input->isKeyDown(sf::Keyboard::Up) && isGrounded == true)
		{
			verticalVel = -350;
		}
		if (input->isKeyDown(sf::Keyboard::Right))
		{
			horizontalVel = 175;
			setFlipped(false);
			directionFacing = sf::Vector2f(1.0f, 0.0f);
			moving = true;
		}
		if (!input->isKeyDown(sf::Keyboard::Left) && !input->isKeyDown(sf::Keyboard::Right))
		{
			horizontalVel = 0;
			moving = false;
		}
		if (input->isKeyDown(sf::Keyboard::Enter) && canAttack)
		{
			Attacking = true;
			currentAnimation = &kick;
		}
		else
		{
			Attacking = false;
			currentAnimation = &walk;
		}
	}
}

bool PlayerSurvival::isDamaged()
{
	return currentAnimation == &damaged;
}
void PlayerSurvival::fireBullet(sf::Vector2f direction, float speed)
{
 	bullets.emplace_back(getPosition(), direction, speed);
}
void PlayerSurvival::update(float dt)
{
	//jumpTime -= dt;
	setCollisionBox(getPosition().x, getPosition().y, getSize().x, getSize().y);

	setVelocity(horizontalVel, verticalVel);
	move(velocity * dt);
	if (!isGrounded)
	{
		verticalVel += 450
			* dt;
	}
	else if (isGrounded)
	{
		verticalVel = 0;
	}
	if (currentAnimation == &damaged)
		damagedTimer += dt;
	if (damagedTimer > damageLength)
	{
		currentAnimation = &walk;
		damagedTimer = 0.f;
	}
	for (auto& bullet : bullets) 
	{
		bullet.update(dt);
	}
	if (currentAnimation == &damaged)
		damagedTimer += dt;
	if (damagedTimer > damageLength)
	{
		currentAnimation = &walk;
		damagedTimer = 0.f;
	}


	currentAnimation->animate(dt);
	setTextureRect(currentAnimation->getCurrentFrame());

}

void PlayerSurvival::setFlipped(bool f)
{
	currentAnimation->setFlipped(f);
}

void PlayerSurvival::setGrounded(bool f)
{
	 isGrounded = f;
}

void PlayerSurvival::setDamaged(float time)
{
	currentAnimation = &damaged;
	damageLength = time;
}

void PlayerSurvival::setAttak(bool f)
{
	canAttack = f;
}


