#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include "Entity.h"
#include "tile.h"
#include "window.h"

class Game
{
private:
    SDL_Texture* mainChar = NULL;
    SDL_Texture* tileTexture = NULL;

    SDL_Rect tileClips[TOTAL_TILE_SPRITES];
    SDL_Rect camera = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};

    bool gameRunning = true;

public:
    bool init();
    bool loadMedia();
    bool isRunning();
    void handleGameInput(SDL_Event& event);
    void destroy();


};
#endif // _GAME_H_
