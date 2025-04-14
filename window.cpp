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
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
	SDL_Rect dst = { entity.getX() - camera.x, entity.getY() - camera.y, rec.w*4, rec.h*4};
	SDL_RenderCopy(renderer, entity.getTexture(), &rec, &dst);
}

void commonFunction::renderAnimation(SDL_Texture* _texture, float _x, float _y, SDL_Rect& _clip, SDL_Rect& _camera, double _angle, SDL_Point* _center, SDL_RendererFlip _flip)
{
    SDL_Rect src = {_clip.x, _clip.y, _clip.w, _clip.h};
    SDL_Rect dst = {_x-_camera.x, _y-_camera.y, _clip.w, _clip.h};
    SDL_RenderCopyEx(renderer,_texture, &_clip, &dst, _angle, _center, _flip);
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

bool commonFunction::touchesWall(SDL_Rect& box, vector<Level>& LevelList) {
	for (int i = 0; i < LevelList.size(); i++) {
		if (box.x > LevelList[i].getX() && box.x + box.w < LevelList[i].getX() + LEVEL_WIDTH && box.y >= 0 && box.y < LEVEL_HEIGHT - TILE_HEIGHT) {
			int cot_left = (box.x - LevelList[i].getX()) / TILE_WIDTH;
			int cot_rigth = cot_left + 1;
			int dong_up = box.y / TILE_HEIGHT;
			int dong_down = dong_up + 1;

			int stt1 = dong_up * 21 + cot_rigth;
			int stt2 = dong_down * 21 + cot_rigth;
			int stt3 = dong_up * 21 + cot_left;
			int stt4 = dong_down * 21 + cot_left;

			if ((LevelList[i].getTilesList()[stt1]->getType() >= 0) && (LevelList[i].getTilesList()[stt1]->getType() <= MAX_TILE))
				if (checkCollision(box, LevelList[i].getTilesList()[stt1]->getCollision())) return true;

			if ((LevelList[i].getTilesList()[stt2]->getType() >= 0) && (LevelList[i].getTilesList()[stt2]->getType() <= MAX_TILE))
				if (checkCollision(box, LevelList[i].getTilesList()[stt2]->getCollision())) return true;


			if ((LevelList[i].getTilesList()[stt3]->getType() >= 0) && (LevelList[i].getTilesList()[stt3]->getType() <= MAX_TILE))
				if (checkCollision(box, LevelList[i].getTilesList()[stt3]->getCollision())) return true;

			if ((LevelList[i].getTilesList()[stt4]->getType() >= 0) && (LevelList[i].getTilesList()[stt4]->getType() <= MAX_TILE))
				if (checkCollision(box, LevelList[i].getTilesList()[stt4]->getCollision())) return true;
		}
	}
	return false;
}

bool commonFunction::touchesWall(SDL_Rect& box, vector<Level>& LevelList, bool& grounded, int& groundSTT, int& levelSTT) {
	bool check = false;
	for (int i = 0; i < LevelList.size(); i++) {
		if (box.x + box.w>= LevelList[i].getX() && box.x <= LevelList[i].getX() + LEVEL_WIDTH && box.y >= 0 && box.y < LEVEL_HEIGHT - TILE_HEIGHT) {
			int cot_left = (box.x - LevelList[i].getX()) / TILE_WIDTH;
			int cot_rigth = cot_left + 1;
			int dong_up = box.y / TILE_HEIGHT;
			int dong_down = dong_up + 1;

			int stt1 = dong_up * 21 + cot_rigth;
			int stt2 = dong_down * 21 + cot_rigth;
			int stt3 = dong_up * 21 + cot_left;
			int stt4 = dong_down * 21 + cot_left;

			if (box.x <= LevelList[i].getX() && box.x + box.w >= LevelList[i].getX() || box.x <= LevelList[i].getX() + LEVEL_WIDTH && box.x + box.w >= LevelList[i].getX() + LEVEL_WIDTH) {
				grounded = false;
			}
			else {
				if ((LevelList[i].getTilesList()[stt1]->getType() >= 0) && (LevelList[i].getTilesList()[stt1]->getType() <= MAX_TILE))
				if (checkCollision(box, LevelList[i].getTilesList()[stt1]->getCollision())) check = true;

			if ((LevelList[i].getTilesList()[stt2]->getType() >= 0) && (LevelList[i].getTilesList()[stt2]->getType() <= MAX_TILE))
				if (checkCollision(box, LevelList[i].getTilesList()[stt2]->getCollision())) check = true;


			if ((LevelList[i].getTilesList()[stt3]->getType() >= 0) && (LevelList[i].getTilesList()[stt3]->getType() <= MAX_TILE))
				if (checkCollision(box, LevelList[i].getTilesList()[stt3]->getCollision())) check = true;

			if ((LevelList[i].getTilesList()[stt4]->getType() >= 0) && (LevelList[i].getTilesList()[stt4]->getType() <= MAX_TILE))
				if (checkCollision(box, LevelList[i].getTilesList()[stt4]->getCollision())) check = true;

				if ((LevelList[i].getTilesList()[stt2]->getType() > MAX_TILE) && (LevelList[i].getTilesList()[stt4]->getType() > MAX_TILE)) grounded = false;
				if ((LevelList[i].getTilesList()[stt4]->getType() > MAX_TILE) && (LevelList[i].getTilesList()[stt2]->getType() <= MAX_TILE) && box.x + box.w <= LevelList[i].getTilesList()[stt2]->getX()) grounded = false;
			}

				groundSTT = stt4;
				levelSTT = i;
		}
	}
	return check;
}

void commonFunction::cleanUp()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = NULL;
    renderer = NULL;

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}

void commonFunction::Color()
{
	surface = SDL_GetWindowSurface(window);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0));
	SDL_UpdateWindowSurface(window);
}

bool commonFunction::loadFont(const char* filePath)
{
	TTF_CloseFont(font);
	font = TTF_OpenFont(filePath, 28);
	if (font == NULL) {
		printf ("Font has failed to load: %s\n",TTF_GetError());
		return false;
	}
	return true;
}
SDL_Texture* commonFunction::createText(string _text, SDL_Color _textColor)
 {
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, _text.c_str(), _textColor);
	SDL_Texture* texture = NULL;
	if (textSurface == NULL) {
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else {
		//Tạo texture text từ surface
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture == NULL) {
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		SDL_FreeSurface(textSurface);
		return texture;
	}
	return NULL;
}

void commonFunction::clearRenderer()
{
    SDL_SetRenderDrawColor(renderer, 38, 212, 255, 255);
    SDL_RenderClear(renderer);
}


void commonFunction::display()
{
    SDL_RenderPresent(renderer);
}
