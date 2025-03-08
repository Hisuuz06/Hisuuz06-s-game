#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Game.h"
#include "window.h"
#include "Entity.h"

using namespace std;

int main(int argc, char* args[])
{
    Game mainGame;
    if(!(mainGame.init())) return 0;
    else{
        while(mainGame.isRunning())
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                mainGame.handleGameInput(event);
            }
        }
    }
    commonFunction::cleanUp;
    return 0;
}
