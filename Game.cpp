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
    if (!(IMG_Init(IMG_INIT_PNG))) {
        std::cout << "IMG_Init HAS FAILED. SDL_ERROR: " << IMG_GetError() << std::endl;
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

    monsterTex = commonFunction::loadTexture("texture/monster.png");
    if(monsterTex == NULL) success = false;

    tileTexture = commonFunction::loadTexture("texture/tile2.png");
    if(tileTexture == NULL) success=false;

    bgTex = commonFunction::loadTexture("texture/bg.jpg");
    if (bgTex == NULL) success = false;

    buttonTex = commonFunction::loadTexture("texture/button.png");
    if (buttonTex == NULL) success = false;

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

void Game::renderScore()
{
    if(score < playerList[0].getX()/TILE_WIDTH) score = playerList[0].getX()/TILE_WIDTH;
    scoreText.str("");
    scoreText<<"Score: "<<score<< "m";
    SDL_Color whiteColor = { 50,255,9,255 };
    SDL_Color yellowColor = { 252,226,5,255 };

    ifstream readFile;
    readFile.open("highscore.txt");
    if (readFile.fail()) update_high_score();
    readFile >> highscore;
    highscoreText.str("");
    highscoreText << "High Score: " << highscore << "m";

    SDL_Texture* scoreTex = commonFunction::createText(scoreText.str().c_str(), yellowColor);
    SDL_Texture* highscoreTex = commonFunction::createText(highscoreText.str().c_str(), whiteColor);
    Entity current_score(1100, 30, scoreTex);
    Entity high_score(1100, 0, highscoreTex);
    commonFunction::renderTexture(current_score);
    commonFunction::renderTexture(high_score);

}

bool Game::createMap()
{
    map_path Map({},"texture/map.map");
    mapList.push_back(Map);
    map_path Map1({8,10,13,12},"texture/map1.map");
    mapList.push_back(Map1);
    map_path Map2({6,10},"texture/map2.map");
    mapList.push_back(Map2);
    map_path Map3({3,12},"texture/map3.map");
    mapList.push_back(Map3);
    map_path Map4({17,12,8,10},"texture/map4.map");
    mapList.push_back(Map4);
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
        Level level(i*LEVEL_WIDTH,0,mapList[random].path,tileTexture);
        level.setMonsterPos(mapList[random].monsterPos);
        LevelList.push_back(level);
    }
    if(LevelList.size()<TOTAL_LEVEL_PART)
    {
        std::cout<<"FAILED TO CREATE LEVEL!"<<endl;
        return false;
    }

    return true;
}

bool Game::createMonster()
{
    for(int i = 0;i<LevelList.size();i++){
        if(LevelList[i].getMonsterPos().size()>0){
            for(int j = 0;j<LevelList[i].getMonsterPos().size()-1;j+=2){
                Monster* monster = new Monster(LevelList[i].getMonsterPos()[j]*TILE_WIDTH+LevelList[i].getX(),LevelList[i].getMonsterPos()[j+1]*TILE_HEIGHT+LevelList[i].getY(),monsterTex);
                monsterList.push_back(monster);
            }
        }
    }
    return true;
}

bool Game::createPlayer()
{
    Player knight(TILE_WIDTH * 3, 300, player);
    playerList.push_back(knight);
    if (playerList.size() < 0) return false;
    return true;
}

bool Game::createMenu()
{
    Menu gameMenu(buttonTex, bgTex);
    menuList.push_back(gameMenu);
    if (menuList.size() < 0) return false;
    return true;
}

void Game::pauseTime()
{
    fpsTimer.pause();
}

void Game::render_update_Level()
{
    if(camera.x >= LevelList[0].getX() + LEVEL_WIDTH)
    {
        int random = rand()%(TOTAL_MAP-1)+1;
        LevelList[0].setTilesType(mapList[random].path);
        LevelList[0].setLevelX(LevelList[LevelList.size()-1]);
        LevelList[0].setMonsterPos(mapList[random].monsterPos);

        if(LevelList[0].getMonsterPos().size()>0){
            for(int j = 0;j<LevelList[0].getMonsterPos().size()-1;j+=2){
                Monster* monster = new Monster(LevelList[0].getMonsterPos()[j]*TILE_WIDTH+LevelList[0].getX(),LevelList[0].getMonsterPos()[j+1]*TILE_HEIGHT+LevelList[0].getY(),monsterTex);
                monsterList.push_back(monster);
            }
        }

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
    playerList[0].update(LevelList, monsterList, camera);
    playerList[0].handleCamera(camera, camVel);
    playerList[0].render(camera);
}

void Game::render_update_monster()
{
    for(int i=0;i<monsterList.size();i++){
        if(monsterList[i]!=NULL){
            if(!monsterList[i]->isDead()){
                monsterList[i]->render(camera);
                monsterList[i]->update(playerList[0],LevelList,camera);
            }
            else{
                delete monsterList[i];
                monsterList[i]==NULL;
                monsterList.erase(monsterList.begin()+i);
            }
        }
    }
}

void Game::update_high_score()
{
    ofstream outFile;
    outFile.open("highscore.txt");
    outFile.clear();
    outFile<<highscore;
    outFile.close();
}

void Game::render_update_Game()
{
    fpsTimer.start();
    commonFunction::clearRenderer();
    render_update_Level();
    render_update_player();
    render_update_monster();
    FPSCounter();
    renderScore();
    if(playerList[0].isDead()){
        menuList[0].renderRetryMenu();
        if( score > highscore) highscore = score;
        update_high_score();
    }
    fpsTimer.unpause();
    if (menuList[0].need_reseting()) resetGame();
    commonFunction::display();
}

void Game::render_mainMenu()
{
    commonFunction::clearRenderer();
    getMenuList()[0].renderMainMenu();
    commonFunction::display();
}

void Game::resetGame()
{
   playerList[0].resetPlayer();
    camera.x = 0;
    camera.y = 0;
    camVel = 1.5;

    if(!monsterList.empty())
    for(int i=monsterList.size()-1;i>=0;i--){
        delete monsterList[i];
        monsterList[i] = NULL;
        monsterList.erase(monsterList.begin()+i);
    }

    for (int i = 0; i < LevelList.size(); i++) {
        int random = rand() % (TOTAL_MAP - 1)+1;
        if (i == 0) {
            random = 0;
            LevelList[i].setLevelX(0);
        }
        else LevelList[i].setLevelX(LevelList[i-1]);
        LevelList[i].setTilesType(mapList[random].path);
        LevelList[i].setMonsterPos(mapList[random].monsterPos);
    }
    createMonster();
    menuList[0].set_reset(false);
    fpsTimer.stop();
    fpsTimer.start();
    countedFrames = 0;
    score = 0;
}


bool Game::isRunning()
{
    return gameRunning;
}

void Game::handleGameInput(SDL_Event& event)
{
    if(event.type==SDL_QUIT) gameRunning = false;
    menuList[0].handleInput(event, gameRunning, playerList[0]);
    if(!menuList[0].isMenu() && !menuList[0].isPaused()) playerList[0].handleInput(event);
}

void Game::setSDL_Rect()
{
    int m = 0, n = 0;
    for (int i = 0; i < TOTAL_TILE_SPRITES; i++) {
        gTileClips[i].x = n;
        gTileClips[i].y = m;
        gTileClips[i].w = TILE_WIDTH/4;
        gTileClips[i].h = TILE_HEIGHT/4;
        n += 16;
        if (n >= 16 * TILE_WIDTH/4) {
            n = 0;
            m += TILE_HEIGHT/4;
        }
    }
}

void Game::destroy()
{
    SDL_DestroyTexture(player);
    SDL_DestroyTexture(tileTexture);
}

