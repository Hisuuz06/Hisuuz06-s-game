#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <ctime>
#include <cstdlib>

#include "Game.h"
#include "window.h"


using namespace std;

int main(int argc, char* argv[])
{
    Game mainGame;
    srand(time(NULL));
    if(!(mainGame.init())) {
        return 0;
    }
    else{
        if(!mainGame.loadMedia()) return 0;
        else
        {
            if(!mainGame.createMap()||!mainGame.createMenu()||!mainGame.createLevel()|| !mainGame.createPlayer())
            {
                std::cout<<"FAILED TO CREATE GAME ELEMENTS!"<<std::endl;
                return 0;
            }
            while(mainGame.isRunning())
            {
                SDL_Event event;
                while (SDL_PollEvent(&event))
                {
                    mainGame.handleGameInput(event);
                }
                if(mainGame.getMenuList()[0].isMenu()) mainGame.render_mainMenu();
                else if(mainGame.getMenuList()[0].isPaused()) mainGame.pauseTime();
                else mainGame.render_update_Game();
            }
        }
    }
    mainGame.destroy();
    commonFunction::cleanUp();
    return 0;
}
