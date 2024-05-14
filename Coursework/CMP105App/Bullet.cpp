#include "Bullet.h"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction, float speed) 
{
    velocity = (direction * speed);
    shape.setSize(sf::Vector2f(15, 15));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(position);
}

//Bullet::~Bullet()
//{
//}


void Bullet::update(float dt)
{
    shape.move(velocity * dt);
}


