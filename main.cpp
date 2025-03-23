#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Game.h"
#include "window.h"


using namespace std;

int main(int argc, char* argv[])
{
    Game mainGame;
    if(!(mainGame.init())) {
        std::cout<<"init";
        return 0;
    }
    else{
        if(!mainGame.loadMedia()) return 0;
        else
        {
            if(!mainGame.createMap()||!mainGame.createLevel())
            {
                std::cout<<"FAILED TO CREATE GAME ELEMENTS!"<<endl;
                return 0;
            }
            while(mainGame.isRunning())
            {
                SDL_Event event;
                while (SDL_PollEvent(&event))
                {
                    mainGame.handleGameInput(event);
                }
                mainGame.render_update_Game();
            }
        }
    }
    mainGame.destroy();
    commonFunction::cleanUp();
    return 0;
}
