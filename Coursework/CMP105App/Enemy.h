#pragma once
#include "Framework/Animation.h"
#include "Framework/GameObject.h"
class Enemy : public GameObject
{
public:
	Enemy();
	~Enemy();
	

	void update(float dt);
	void move(const sf::Vector2f& playerPosition);
	void render();

	void setType();

	int Health = 0;
	float moveSpeed = 0;


	
	sf::Texture sprite;
	Animation walk;
	Animation* currentAnimation;


};

