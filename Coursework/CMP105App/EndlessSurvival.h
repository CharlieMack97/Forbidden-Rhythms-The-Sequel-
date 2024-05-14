#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/BaseLevel.h"
#include "Framework/GameObject.h"
#include "PlayerSurvival.h"
#include "Enemy.h"
#include "ScrollingBG.h"
#include "Framework/Collision.h"
#include "TextureManager.h"
#include <iostream>
#include <random>
class EndlessSurvival : BaseLevel
{
public:
	EndlessSurvival(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud, TextureManager* tm);

	~EndlessSurvival();

	void handleInput(float dt) override;
	void update(float dt) override;
	void render() override;
	bool colliding(GameObject obj);
	void reset();
	void setPlayers(bool t) {players1 = t; };
	void destroyEnemy(Enemy* enemy);
	void spawnEnemy();

	TextureManager* textMan;
	PlayerSurvival p1;
	PlayerSurvival p2;
	ScrollingBG bg;

	Enemy erin;
	Enemy erin2;
	Enemy erin3;

	Enemy will;
	std::vector<Enemy*>enemyErin;
	std::vector<GameObject>enemyWill;

	GameObject ground;

	int maxEnemies = 5;
	int Kills = 0;
	float time = 0;

	bool players1 = true;
	float playerSpeedP1 = 0;

	sf::View view;
	sf::Clock updateTimer;

	sf::Text Score;

	sf::RectangleShape Hp1, Hp2;
	GameObject HPBar1, HPBar2;
	sf::Texture bgTexture1, bgTexture2, bgTexture3, bgTexture4;
	sf::Sprite bgLayer1, bgLayer2, bgLayer3, bgLayer4;

	sf::Font font;

	const float TIME_PER_STEP = 1.0f;	// time for each step (time between claps)
	const float TIME_FOR_ACTION = 0.25f;	// how long (seconds) does the player have to act
	const float TIME_BUFFER = 0.25f;	// time between end of action window and end of step.
	const float RESET_TIME = 1.0f;		// time for 'reset' state where player cannot move.
	float timeLeft = 0;
	float timeInStep = 0;
	GameObject progressInStep;
	GameObject targetZone;
	GameObject progressInStepBG;

private:
	std::mt19937 gen; // Random number engine
	std::uniform_int_distribution<int> xDistribution; // Distribution for x coordinate
	std::uniform_int_distribution<int> yDistribution; // Distribution for y coordinate
};

