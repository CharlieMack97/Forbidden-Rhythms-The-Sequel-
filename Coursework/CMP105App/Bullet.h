#pragma once
#include "Framework/GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet(sf::Vector2f position, sf::Vector2f direction, float speed);
	//~Bullet();

	sf::RectangleShape shape;
	sf::Vector2f velocity;

	
	void update(float dt);
	
};

