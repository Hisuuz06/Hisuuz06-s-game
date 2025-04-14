#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <sstream>
#include <fstream>
#include <ctime>
#include <cstdlib>

#include "Entity.h"
#include "tile.h"
#include "window.h"
#include "Timer.h"
#include "Level.h"
#include "Player.h"
#include "Monster.h"
#include "Menu.h"

class Game
{
private:
    SDL_Texture* player = NULL;
    SDL_Texture* monsterTex = NULL;
    SDL_Texture* tileTexture = NULL;
    SDL_Texture* bgTex = NULL;
    SDL_Texture* buttonTex = NULL;

    Mix_Music* bgMusic = NULL;
    Mix_Chunk* playerSFX[4] = { NULL };
    Mix_Chunk* monsterSFX = NULL;

    SDL_Rect gTileClips[TOTAL_TILE_SPRITES];
    SDL_Rect camera = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    float camVel = 1.5;

    LTimer fpsTimer;
    stringstream timeText;
    stringstream scoreText;
    stringstream highscoreText;
    int score = 0;
    int killScore = 0;
    int distanceScore = 0;
    int highscore = 0;
    int countedFrames = 0;

    bool gameRunning = true;
    vector<map_path> mapList;
    vector<Level> LevelList;
    vector<Monster*> monsterList;
    vector<Player> playerList;
    vector<Menu> menuList;

public:
    Game()
    {
        setSDL_Rect();
    }
    bool init();
    bool loadMedia();
    void FPSCounter();
    void renderScore();
    bool createMap();
    bool createLevel();
    bool createMonster();
    bool createPlayer();
    bool createMenu();
    void playMusic();
    void pauseTime();
    void render_update_Level();
    void render_update_player();
    void render_update_monster();
    void update_high_score();
    void render_update_Game();
    void render_mainMenu();
    void resetGame();
    bool isRunning();
    void handleGameInput(SDL_Event& event);
    vector<Menu> getMenuList() { return menuList; }
    void setSDL_Rect();
    void destroy();
};
#endif // _GAME_H_
