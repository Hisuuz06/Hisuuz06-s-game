#ifndef _ENTITY_H_
#define _ENTITY_H_
#include<SDL.h>
#include<SDL_image.h>
class Entity
{
protected:
    float x,y;
    SDL_Rect currentFrame;
    SDL_Texture* texture=NULL;
    SDL_RendererFlip flipType = SDL_FLIP_NONE;
public:
    Entity(float _x, float _y, SDL_Texture* _texture);
    float getX();
    float getY();
    SDL_Rect getCurrentFrame();
    SDL_Texture* getTexture();
    SDL_RendererFlip getFlipType();

};

#endif // _ENTITY_H_
