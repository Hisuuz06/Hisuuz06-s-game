#ifndef _WINDOW__H
#define _WINDOW__H

#include <SDL.h>
#include <SDL_image.h>
#include "Entity.h"
#include "tile.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;


const int TILE_WIDTH=8;
const int TILE_HEIGHT=8;
const int TOTAL_TILES = 336;
const int TOTAL_TILE_SPRITES = 187;


static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
//static SDL_Surface* surface = NULL;

namespace commonFunction
{
    void RenderWindow (const char* Window_Tittle, int Window_Width, int WIndow_Height);


    SDL_Texture* loadTexture(const char* FilePath);
    void renderTexture(Entity& entity, SDL_Rect *rec = NULL, SDL_Rect *camera = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void renderTexture(SDL_Texture* _texture, float _x, float _y, float _w = 0, float _h = 0, SDL_Rect* rec = NULL, SDL_Rect* camera = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void renderTile(Entity& entity, SDL_Rect& rec, SDL_Rect& camera);


    void clearRenderer();
    void display();
    void cleanUp();


}

#endif // _WINDOW__H
