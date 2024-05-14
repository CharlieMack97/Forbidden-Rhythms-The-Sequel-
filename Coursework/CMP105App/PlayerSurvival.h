#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include "Framework/Input.h"
#include "Bullet.h"
class PlayerSurvival : public GameObject
{
public:
	PlayerSurvival();
	~PlayerSurvival();


	void handleInput(float dt);
	bool isDamaged();
	void update(float dt);
	void setFlipped(bool f);
	void setPlayerNum(int num) { playerNum = num; }
	void fireBullet(sf::Vector2f direction, float speed);
	void setGrounded(bool f);
	void setDamaged(float time);
	bool isMoving() { return moving; };
	void setAttak(bool f);
	bool isAttacking() { return Attacking; };
	const std::vector<Bullet>& getBullets() const { return bullets; }
	sf::Texture dino;
	Input in;
	Animation walk;
	Animation damaged;
	Animation kick;
	Animation* currentAnimation;

	float damagedTimer = 0.f;
	float damageLength = 100.0f;
	float ammoReloadTimer = 30.f;

	bool canAttack = true;
	bool Attacking = false;
	bool isGrounded = false;
	bool moving = false;
	int playerNum = 0;
	int health = 0;
	int ammo = 5;

	float verticalVel = 0.f;
	float horizontalVel = 0.f; 
	float bulletSpeed = 0.f;
	std::vector<Bullet> bullets;
	sf::Vector2f directionFacing;
};

