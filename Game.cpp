#include "Game.h"

bool Game::init()
{
    bool success = true;
    if(SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
        std::cout << "SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
        success = false;
    }
    if(!IMG_Init(IMG_INIT_PNG))
    {
        std::cout << "SDL_Init HAS FAILED. ERROR: " << IMG_GetError << std::endl;
        success = false;
    }
    if (success == true) commonFunction::RenderWindow("Hisuuz06's Game", SCREEN_WIDTH, SCREEN_HEIGHT);
    return success;
}

/*bool Game::loadMedia()
{
    bool success = true;
    mainChar = commonFunction::loadTexture();
    if(mainChar == NULL) success = false;

    tileTexture == commonFunction::loadTexture();
    if(tileTexture == NULL) success=false;
}*/

bool Game::isRunning()
{
    return gameRunning;
}

void Game::handleGameInput(SDL_Event& event)
{
    if(event.type==SDL_QUIT) gameRunning == false;
}

