#pragma once
#include "Framework/GameObject.h"
class ScrollingBG : public GameObject
{
public:
	ScrollingBG();
	~ScrollingBG();

	void update(float playerPosX, float windowH,float windowW);
	void render(sf::RenderWindow& window) const;

private:

	const int WINDOW_WIDTH = 1900;
	static const int NUM_LAYERS = 4; // Number of background layers
	static const int NUM_IMAGES_PER_LAYER = 5;
	
	sf::Texture textures[NUM_LAYERS];
	sf::Sprite sprites[NUM_LAYERS][NUM_IMAGES_PER_LAYER];

	
	float parallaxFactors[NUM_LAYERS] = { 0.8f, 0.6f, 0.4f, 0.1f }; // Parallax factors for each layer
};

