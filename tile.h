#ifndef _TILE_H_
#define _TILE_H_

#include "Entity.h"
#include "window.h"

class Tile : public Entity
{
    public:
		Tile( float _x, float _y,SDL_Texture* _texture, int _tileType );
		int getType();
		SDL_Rect getCollision();
		void setX(int _x);
		void setType(int _tileType);

    private:
		SDL_Rect collision;
		int tileType;
};
#endif // _TILE_H_
