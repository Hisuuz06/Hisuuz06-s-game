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

bool Game::loadMedia()
{
    bool success = true;
    /*player = commonFunction::loadTexture();
    if(player == NULL) success = false;*/

    tileTexture = commonFunction::loadTexture("texture/tile.png");
    if(tileTexture == NULL) success=false;

    if (!success) cout << "FAILED TO LOAD MEDIA: " << SDL_GetError() << endl;
    return success;
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
        int random=rand()%(TOTAL_MAP-1);
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
void Game::render_update_Game()
{
    commonFunction::clearRenderer();
    camera.x=camera.x+camVel;
    /*if (camera.x > LEVEL_WIDTH - SCREEN_WIDTH) {
    camera.x = LEVEL_WIDTH - SCREEN_WIDTH;
    }*/
    render_update_Level();
    commonFunction::display();
}

bool Game::isRunning()
{
    return gameRunning;
}

void Game::handleGameInput(SDL_Event& event)
{
    if(event.type==SDL_QUIT) gameRunning = false;
}

void Game::setSDL_Rect()
{
    int m = 0, n = 0;
    for (int i = 1; i <= TOTAL_TILE_SPRITES; i++) {
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

