#include "EndlessSurvival.h"

EndlessSurvival::EndlessSurvival(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud, TextureManager* tm) : gen(std::random_device()()), xDistribution(0, 800), yDistribution(0, 600)
{
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;
	textMan = tm;
	
	//bool players1 = true;

	p1.setPlayerNum(1);
	p2.setPlayerNum(2);

	p1.setPosition(250, 800);
	p2.setPosition(250, 800);

	p1.setInput(in);
	p2.setInput(in);

	ground.setSize(sf::Vector2f(1650, 50));
	ground.setPosition(-800, 855);
	ground.setCollisionBox(ground.getPosition().x, ground.getPosition().y, 32000.f, ground.getSize().y);
	ground.setFillColor(sf::Color::Green);

	HPBar1.setSize(sf::Vector2f(16, 16));
	HPBar2.setSize(sf::Vector2f(16, 16));

	HPBar1.setTexture(&textMan->getTexture("HPBar"));
	HPBar2.setTexture(&textMan->getTexture("HPBar"));

	HPBar1.setScale(sf::Vector2f(3, 3));
	HPBar2.setScale(sf::Vector2f(3, 3));


	Hp1.setSize(sf::Vector2f(48.f, 30.4f));
	Hp1.setFillColor(sf::Color::Red);

	Hp2.setSize(sf::Vector2f(48.f, 30.4f));
	Hp2.setFillColor(sf::Color::Red);


	erin.setPosition(200, 600);
	erin2.setPosition(600, 300);
	erin3.setPosition(0, 150);
	//sf::View view = window->getDefaultView();


	// Setup progress bar component.
	progressInStep.setPosition(sf::Vector2f(400, 200));
	progressInStep.setSize(sf::Vector2f(0, 200));
	progressInStepBG.setPosition(sf::Vector2f(400, 190));
	progressInStepBG.setSize(sf::Vector2f(500, 220));
	progressInStepBG.setFillColor(sf::Color::Black);
	targetZone.setPosition(sf::Vector2f(
		progressInStepBG.getPosition().x + progressInStepBG.getSize().x * (TIME_PER_STEP - TIME_FOR_ACTION - TIME_BUFFER) / TIME_PER_STEP,
		790
	));
	targetZone.setSize(sf::Vector2f(
		progressInStepBG.getSize().x * (TIME_FOR_ACTION / TIME_PER_STEP),
		220
	));
	targetZone.setFillColor(sf::Color::Blue);



}

EndlessSurvival::~EndlessSurvival()
{
}

void EndlessSurvival::handleInput(float dt)
{
	p1.handleInput(dt);
	p2.handleInput(dt);
}

void EndlessSurvival::update(float dt)
{
	timeInStep += dt;
	progressInStep.setSize(sf::Vector2f((timeInStep / TIME_PER_STEP) * progressInStepBG.getSize().x,200));
	float timeLeft = TIME_PER_STEP - timeInStep;
	if (timeLeft > TIME_BUFFER && timeLeft < TIME_BUFFER + TIME_FOR_ACTION && p1.canAttack == false)
	{
		progressInStep.setFillColor(sf::Color::Green);
		p1.setAttak(true);
		p2.setAttak(true);
		
	}
	else
	{
		progressInStep.setFillColor(sf::Color::Red);
	}
	if (timeLeft < 0)
	{
		timeLeft = 2.f;
	}
	time += dt;
	if (p1.health <= 0)
	{
		audio->playSoundbyName("success");
		erin.setPosition(sf::Vector2f(100, 400));
		erin2.setPosition(sf::Vector2f(400, 400));
		erin3.setPosition(sf::Vector2f(800, 400));
		p1.health = 100;
		p2.health = 100;


		gameState->addResult("l4Kills", Kills);
		gameState->addResult("l4Time", time);
		gameState->setCurrentState(State::ENDGAME);
	}
	else if (p2.health <= 0)
	{
		audio->playSoundbyName("success");
		erin.setPosition(sf::Vector2f(100, 400));
		erin2.setPosition(sf::Vector2f(400, 400));
		erin3.setPosition(sf::Vector2f(800, 400));
		p1.health = 100;
		p2.health = 100;
		gameState->addResult("l4Kills", Kills);
		gameState->addResult("l4Time", time);
		if (gameState->getSingleRun()) gameState->setCurrentState(State::ENDGAME);
		else gameState->setCurrentState(State::ENDGAME);
	}
	if (Collision::checkBoundingBox(&p1, &erin) && p1.Attacking == false)
	{
		p1.setDamaged(5);
		p1.health -= 15;
		int randomX = xDistribution(gen);
		int randomY = yDistribution(gen);
		erin.setPosition(randomX, randomY);
	}
	else  if (Collision::checkBoundingBox(&p1, &erin) && p1.Attacking == true) {
		int randomX = xDistribution(gen);
		int randomY = yDistribution(gen);
		erin.setPosition(randomX, randomY);
	}
	if (Collision::checkBoundingBox(&p1, &erin2) && p1.Attacking == false)
	{
		p1.setDamaged(5);
		p1.health -= 15;
		int randomX = xDistribution(gen);
		int randomY = yDistribution(gen);
		erin2.setPosition(randomX, randomY);
	}
	else  if(Collision::checkBoundingBox(&p1, &erin2) && p1.Attacking == true)
	{
		int randomX = xDistribution(gen);
		int randomY = yDistribution(gen);
		erin2.setPosition(randomX, randomY);
	}
	if (Collision::checkBoundingBox(&p1, &erin3) && p1.Attacking == false)
	{
		p1.setDamaged(5);
		p1.health -= 15;
		int randomX = xDistribution(gen);
		int randomY = yDistribution(gen);
		erin3.setPosition(randomX, randomY);
	}
	else if (Collision::checkBoundingBox(&p1, &erin3) && p1.Attacking == true) {
		int randomX = xDistribution(gen);
		int randomY = yDistribution(gen);
		erin3.setPosition(randomX, randomY);
	}
	if (Collision::checkBoundingBox(&p2, &erin) && p2.Attacking == false)
	{
		p2.setDamaged(5);
		p2.health -= 15;
		int randomX = xDistribution(gen);
		int randomY = yDistribution(gen);
		erin.setPosition(randomX, randomY);
	}
	else  if (Collision::checkBoundingBox(&p2, &erin) && p2.Attacking == true)
	{
		int randomX = xDistribution(gen);
		int randomY = yDistribution(gen);
		erin.setPosition(randomX, randomY);
	}
	if (Collision::checkBoundingBox(&p2, &erin2) &&p2.Attacking == false)
	{
		p2.setDamaged(5);
		p2.health -= 15;
		int randomX = xDistribution(gen);
		int randomY = yDistribution(gen);
		erin2.setPosition(randomX, randomY);
	}
	else  if (Collision::checkBoundingBox(&p2, &erin2) && p2.Attacking == true)
	{
		int randomX = xDistribution(gen);
		int randomY = yDistribution(gen);
		erin2.setPosition(randomX, randomY);
	}
	if (Collision::checkBoundingBox(&p2, &erin3) && p2.Attacking == false)
	{
		p2.setDamaged(5);
		p2.health -= 15;
		int randomX = xDistribution(gen);
		int randomY = yDistribution(gen);
		erin3.setPosition(randomX, randomY);
	}
	else if (Collision::checkBoundingBox(&p2, &erin3) && p2.Attacking == true)
	{
		int randomX = xDistribution(gen);
		int randomY = yDistribution(gen);
		erin3.setPosition(randomX, randomY);
	}
	if (players1 == true)
	{
		view.setCenter(p1.getPosition().x, window->getSize().y / 2);
		view.setSize(sf::Vector2f(window->getSize().x, window->getSize().y)); // Set the size of the view to match the window size
		bg.update(p1.getPosition().x, view.getSize().x, view.getSize().y);
		if (Collision::checkBoundingBox(&p1, &ground))
		{
			p1.setGrounded(true);
		}
		else
		{
			p1.setGrounded(false);
		}
		if (p1.getPosition().y > 900)
		{
			p1.setPosition(50, 50);
			p1.setDamaged(6.f);
			p1.health -= 25;
		}
		if (p1.getPosition().x > 900)
		{
			p1.move(-1, 0);
		}
		if (p1.getPosition().x < -600)
		{
			p1.move(0, 0);
		}
		//Code for updating the health bar;
		float healthPercent1 = static_cast<float>(p1.health) / 100.f;
		HPBar1.setPosition(sf::Vector2f(p1.getPosition().x + 25, p1.getPosition().y - 35));
		Hp1.setPosition(sf::Vector2f(p1.getPosition().x + 25, p1.getPosition().y - 20));
		Hp1.setScale(sf::Vector2f((1 * healthPercent1), 1));


		p1.update(dt);//Update the player
	}
	else
	{
		sf::Vector2f midpoint = (p1.getPosition() + p2.getPosition()) / 2.0f;
		if (midpoint.x - view.getSize().x / 2.0f <= 0) {
			view.setCenter(view.getSize().x / 2.0f, midpoint.y);
		}
		if (midpoint.x + view.getSize().x / 2.0f >= 1600) { // Assuming the total game width is 1600
			view.setCenter(1600 - view.getSize().x / 2.0f, midpoint.y);
		}

		view.setCenter(midpoint.x, window->getSize().y / 2);
		view.setSize(sf::Vector2f(window->getSize().x, window->getSize().y)); // Set the size of the view to match the window size
		bg.update(p1.getPosition().x, view.getSize().x, view.getSize().y);
		if (Collision::checkBoundingBox(&p1, &ground))
		{
			p1.setGrounded(true);
		}
		else
		{
			p1.setGrounded(false);
		}
		if (Collision::checkBoundingBox(&p2, &ground))
		{
			p2.setGrounded(true);
		}
		else
		{
			p2.setGrounded(false);
		}

		//bg.update(playerSpeedP1);
		if (p1.getPosition().y > 900)
		{
			p1.setPosition(50, 50);
			p1.setDamaged(6.f);
			p1.health -= 25;
		}
		if (p1.getPosition().x > 900)
		{
			p1.move(-1, 0);
		}
		if (p1.getPosition().x < -600)
		{
			p1.move(0, 0);
		}
		if (p2.getPosition().y > 900)
		{
			p2.setPosition(50, 50);
			p2.setDamaged(6.f);
			p2.health -= 25;
		}
		if (p2.getPosition().x > 900)
		{
			p2.move(-1, 0);
		}
		if (p1.getPosition().x < -600)
		{
			p2.move(0, 0);
		}
		float healthPercent1 = static_cast<float>(p1.health) / 100.f;
		HPBar1.setPosition(sf::Vector2f(p1.getPosition().x + 25, p1.getPosition().y - 35));
		Hp1.setPosition(sf::Vector2f(p1.getPosition().x + 25, p1.getPosition().y - 20));
		Hp1.setScale(sf::Vector2f((1 * healthPercent1), 1));


		float healthPercent2 = static_cast<float>(p2.health) / 100.f;
		HPBar2.setPosition(sf::Vector2f(p2.getPosition().x + 25, p2.getPosition().y - 35));
		Hp2.setPosition(sf::Vector2f(p2.getPosition().x + 25, p2.getPosition().y - 20));
		Hp2.setScale(sf::Vector2f((1 * healthPercent2), 1));

		erin3.move(p2.getPosition());
		erin3.update(dt);
		p1.update(dt);
		p2.update(dt);
	}
	
	erin.move(p1.getPosition());
	erin.update(dt);
	erin2.move(p1.getPosition());
	erin2.update(dt);
}

void EndlessSurvival::render()
{
	beginDraw();
	window->clear();
	window->setView(view);
	bg.render(*window);
	window->draw(ground);
	if (players1 == true)
	{
		window->clear();
		bg.render(*window);
		window->draw(ground);
		window->draw(p1);
		window->draw(Hp1);
		window->draw(HPBar1);
	
	}
	else 
	{
		window->clear();
		bg.render(*window);
		window->draw(ground);
		window->draw(p1);
		window->draw(Hp1);
		window->draw(HPBar1);
		window->draw(p2);
		window->draw(Hp2);
		window->draw(HPBar2);
		window->draw(erin3);
	}
	/*window->draw(progressInStep);
	window->draw(progressInStepBG);
	window->draw(targetZone);*/

	window->draw(erin);
	window->draw(erin2);
	
	endDraw();
}


//void EndlessSurvival::reset()
//{
//}
//
//void EndlessSurvival::destroyEnemy(Enemy* enemy)
//{
//	auto it = std::find(enemyErin.begin(), enemyErin.end(), enemy);
//	if (it != enemyErin.end()) {
//		// Remove the enemy from the vector
//		delete* it; // Remember to delete the object to avoid memory leaks
//		enemyErin.erase(it);
//	}
//}
//
//void EndlessSurvival::spawnEnemy()
//{
//	Enemy* newEnemy = new Enemy();
//	enemyErin.push_back(newEnemy);
//
//}




