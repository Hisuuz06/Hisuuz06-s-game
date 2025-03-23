#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <fstream>
#include "tile.h"
#include "window.h"

using namespace std;

class Level
{
private:
    float x, y;
    vector<Tile*> TilesList;
public:
    Level(float _x, float _y,const char* _path, SDL_Texture* _tileTex );
    void render(SDL_Rect _TileClips[], SDL_Rect& _camera);

    void setLevelX(Level& _level);
	void setLevelX(float _x);
    void setTilesType(const char* _path);

    vector<Tile*> getTilesList();

    int getX();
    int getY();

};
#endif // _LEVEL_H_
