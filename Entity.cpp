#include "Entity.h"

Entity::Entity(float _x,float _y,SDL_Texture* _texture)
{
    x=_x;
    y=_y;
    texture=_texture;
    currentFrame.x = 0;
    currentFrame.y = 0;
}
SDL_Rect Entity::getCurrentFrame()
{
    return currentFrame;
}

SDL_Texture* Entity::getTexture()
{
    return texture;
}

float Entity::getX()
{
    return x;
}

float Entity::getY()
{
    return y;
}


