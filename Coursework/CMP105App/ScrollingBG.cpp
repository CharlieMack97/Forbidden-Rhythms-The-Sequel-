#include "ScrollingBG.h"

ScrollingBG::ScrollingBG()
{
    // Load texture for each layer
    for (int i = 0; i < NUM_LAYERS; ++i) {
        if (!textures[i].loadFromFile("gfx/bg_Scroll-" + std::to_string(i + 1) + ".png")) {
            // Handle error
            exit(EXIT_FAILURE);
        }
        // Create and position multiple sprites for each layer
        for (int j = 0; j < NUM_IMAGES_PER_LAYER; ++j) {
            sprites[i][j].setTexture(textures[i]);
            sprites[i][j].setPosition(j * textures[i].getSize().x, 0);
        }
    }
}

ScrollingBG::~ScrollingBG()
{
}

void ScrollingBG::update(float playerPosX, float windowWidth, float windowHeight)
{
    for (int i = 0; i < NUM_LAYERS; ++i)
    {
        float layerWidth = textures[i].getSize().x * NUM_IMAGES_PER_LAYER; // Calculate total width of the layer
        float movement = -playerPosX * parallaxFactors[i]; // Calculate movement based on player's X position

        // Loop through each image in the layer
        for (int j = 0; j < NUM_IMAGES_PER_LAYER; ++j)
        {
            // Calculate position for each sprite
            float spriteX = movement + j * textures[i].getSize().x;
            float spriteY = windowHeight - textures[i].getSize().y; // Adjust Y position to cover the screen

            // If sp rite moves ff screen to the left, reposition it to the right
            if (spriteX + textures[i].getSize().x < 0)
            {
                spriteX += layerWidth;
            }
            // If sprite moves off screen to the right, reposition it to the left
            else if (spriteX > windowWidth)
            {
                spriteX -= layerWidth;
            }

            // Set position for each sprite
            sprites[i][j].setPosition(spriteX, spriteY);
        }
    }
}

void ScrollingBG::render(sf::RenderWindow& window) const
{
    // Draw each layer
    for (int i = 0; i < NUM_LAYERS; ++i) 
    {
        for (int j = 0; j < NUM_IMAGES_PER_LAYER; ++j)
        {
            window.draw(sprites[i][j]);
        }
    }
}
