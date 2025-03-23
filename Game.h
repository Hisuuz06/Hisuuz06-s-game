#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <fstream>
#include <ctime>

#include "Entity.h"
#include "tile.h"
#include "window.h"
#include "Level.h"

class Game
{
private:
    SDL_Texture* player = NULL;
    SDL_Texture* tileTexture = NULL;

    SDL_Rect gTileClips[TOTAL_TILE_SPRITES+1];
    SDL_Rect camera = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};

    bool gameRunning = true;
    vector<char*> mapList;
    vector<Level> LevelList;

public:
    Game()
    {
        setSDL_Rect();
    }
    bool init();
    bool loadMedia();
    bool createMap();
    bool createLevel();
    void render_update_Level();
    void render_update_Game();
    bool isRunning();
    void handleGameInput(SDL_Event& event);
    void setSDL_Rect();
    void destroy();


};
#endif // _GAME_H_
