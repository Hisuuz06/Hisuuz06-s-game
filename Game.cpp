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
    if (TTF_Init() == -1) {
        std::cout << "TTF_Init HAS FAILED. SDL_ERROR: " << TTF_GetError() << std::endl;
        success = false;
    }
    if (success == true) commonFunction::RenderWindow("Hisuuz06's Game", SCREEN_WIDTH, SCREEN_HEIGHT);
    return success;
}

bool Game::loadMedia()
{
    bool success = true;
    if (!commonFunction::loadFont("font/Pixel-UniCode.ttf")) success = false;

    player = commonFunction::loadTexture("texture/knight2.png");
    if(player == NULL) success = false;

    tileTexture = commonFunction::loadTexture("texture/tile.png");
    if(tileTexture == NULL) success=false;

    if (!success) cout << "FAILED TO LOAD MEDIA: " << SDL_GetError() << endl;
    return success;
}

void Game::FPSCounter()
{
    int avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
    if (avgFPS > 2000000) {
        avgFPS = 0;
    }
    timeText.str("");
    timeText << "FPS: " << avgFPS;

    SDL_Color whiteColor = { 255,255,255,255 };
    SDL_Texture* textTex = commonFunction::createText(timeText.str().c_str(), whiteColor);
    Entity text(64, 0, textTex);
    commonFunction::renderTexture(text);
    ++countedFrames;
}

bool Game::createMap()
{
    mapList.push_back("texture/map.map");
    mapList.push_back("texture/map1.map");
    mapList.push_back("texture/map2.map");
    mapList.push_back("texture/map3.map");
    mapList.push_back("texture/map4.map");
    if(mapList.size()<TOTAL_MAP)
    {
        std::cout<<"FAILED TO LOAD MAP!"<<endl;
        return false;
    }
    return true;

}

bool Game::createLevel()
{
    for(int i =0 ;i<TOTAL_LEVEL_PART;i++)
    {
        int random=rand()%(TOTAL_MAP-1)+1;
        if(i==0) random=0;
        Level level(i*LEVEL_WIDTH,0,mapList[random],tileTexture);
        LevelList.push_back(level);
    }
    if(LevelList.size()<TOTAL_LEVEL_PART)
    {
        std::cout<<"FAILED TO CREATE LEVEL!"<<endl;
        return false;
    }

    return true;
}


bool Game::createPlayer()
{
    Player knight(64 * 3, 300, player);
    playerList.push_back(knight);
    if (playerList.size() < 0) return false;
    return true;
}

void Game::render_update_Level()
{
    if(camera.x >= LevelList[0].getX() + LEVEL_WIDTH)
    {
        int random = rand()%(TOTAL_MAP-1)+1;
        LevelList[0].setTilesType(mapList[random]);
        LevelList[0].setLevelX(LevelList[LevelList.size()-1]);

        Level level=LevelList[0];
        LevelList.erase(LevelList.begin());
        LevelList.push_back(level);
    }
    for(int i=0;i<LevelList.size();i++)
    {
        LevelList[i].render(gTileClips,camera);
    }
}

void Game::render_update_player()
{
    playerList[0].update(LevelList, camera);
    playerList[0].handleCamera(camera, camVel);
    playerList[0].render(camera);
}

void Game::render_update_Game()
{
    fpsTimer.start();
    commonFunction::clearRenderer();
    render_update_Level();
    render_update_player();
    FPSCounter();
    fpsTimer.unpause();
    commonFunction::display();
}

bool Game::isRunning()
{
    return gameRunning;
}

void Game::handleGameInput(SDL_Event& event)
{
    playerList[0].handleInput(event);
    if(event.type==SDL_QUIT) gameRunning = false;
}

void Game::setSDL_Rect()
{
    int m = 0, n = 0;
    for (int i = 0; i < TOTAL_TILE_SPRITES; i++) {
        gTileClips[i].x = n;
        gTileClips[i].y = m;
        gTileClips[i].w = TILE_WIDTH;
        gTileClips[i].h = TILE_HEIGHT;
        n += TILE_WIDTH;
        if (n >= 8 * TILE_WIDTH) {
            n = 0;
            m += TILE_HEIGHT;
        }
    }
}

void Game::destroy()
{
    SDL_DestroyTexture(player);
    SDL_DestroyTexture(tileTexture);
}

