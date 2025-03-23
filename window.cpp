#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "window.h"

void commonFunction::RenderWindow(const char* Window_Tittle, int Window_Width, int Window_Height)
{
    window = SDL_CreateWindow(Window_Tittle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Window_Width, Window_Height, SDL_WINDOW_SHOWN);
    if(window == NULL)
    {
        std::cout << "Window has failed to init. ERROR: " << SDL_GetError() << std::endl;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
		std::cout << "Renderer has failed to init. ERROR: " << SDL_GetError() << std::endl;
	}
}

SDL_Texture* commonFunction::loadTexture(const char* FilePath)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer,FilePath);
    if (texture == NULL)
        std::cout << "Texture has failed to load. ERROR: " << IMG_GetError() << std::endl;
    return texture;
}


//Copy texture vào renderer và render
void commonFunction::renderTexture(Entity& entity, SDL_Rect *rec, SDL_Rect *camera, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//mặc định là in toàn bộ texture ra
	SDL_Rect dst = { entity.getX(), entity.getY(), entity.getCurrentFrame().w, entity.getCurrentFrame().h };

	//nếu đầu vào rec != NULL thì in ra theo rec
	if (rec != NULL) {
		dst.w = rec->w;
		dst.h = rec->h;
	}
	if (camera != NULL) {
		dst.x = dst.x - camera->x;
		dst.y = dst.y - camera->y;
	}
	SDL_RenderCopyEx(renderer, entity.getTexture(), rec, &dst, angle, center, flip);
}

void commonFunction::renderTexture(SDL_Texture* p_tex, float p_x, float p_y, float p_w, float p_h, SDL_Rect* rec, SDL_Rect* camera, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//mặc định là in toàn bộ texture ra
	SDL_Rect dst = { p_x, p_y, p_w, p_h };

	//nếu đầu vào rec != NULL thì in ra theo rec
	if (rec != NULL) {
		dst.w = rec->w;
		dst.h = rec->h;
	}
	if (camera != NULL) {
		dst.x = dst.x - camera->x;
		dst.y = dst.y - camera->y;
	}
	SDL_RenderCopyEx(renderer, p_tex, rec, &dst, angle, center, flip);
}

void commonFunction::renderTile(Entity& entity, SDL_Rect& rec, SDL_Rect& camera)
{
	SDL_Rect dst = { entity.getX() - camera.x, entity.getY() - camera.y, rec.w, rec.h };
	SDL_RenderCopy(renderer, entity.getTexture(), &rec, &dst);
}

bool commonFunction::checkCollision(SDL_Rect a, SDL_Rect b)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	if (bottomA <= topB) {
		return false;
	}

	if (topA >= bottomB) {
		return false;
	}

	if (rightA <= leftB) {
		return false;
	}

	if (leftA >= rightB) {
		return false;
	}

	return true;
}

void commonFunction::cleanUp()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = NULL;
    renderer = NULL;

    SDL_Quit();
    IMG_Quit();
}


void commonFunction::clearRenderer()
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
}


void commonFunction::display()
{
    SDL_RenderPresent(renderer);
}
