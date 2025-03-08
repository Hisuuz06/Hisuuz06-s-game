#include "tile.h"
Tile::Tile(float _x, float _y, SDL_Texture* _texture,int _tileType) : Entity(_x,_y,_texture)
{
    collision.x=_x;
    collision.y=_y;
    collision.w=TILE_WIDTH;
    collision.h=TILE_HEIGHT;

    tileType=_tileType;
}
void Tile::setType(int _tileType)
{
    tileType=_tileType;
}

int Tile::getType()
{
    return tileType;
}

SDL_Rect Tile::getCollision()
{
    return collision;
}

void Tile::setX(int _x)
{
    x=_x;
    collision.x=getX();
}
