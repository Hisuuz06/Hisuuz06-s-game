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

class Tile;
class Level
{
private:
    float x, y;
    vector<Tile*> TilesList;
    vector<float> monsterPos;
public:
    Level(float _x, float _y,const char* _path, SDL_Texture* _tileTex );
    void render(SDL_Rect _TileClips[], SDL_Rect& _camera);

    void setLevelX(Level& _level);
	void setLevelX(float _x);
    void setTilesType(const char* _path);
    void setMonsterPos(vector<float>& _monsterPos) { monsterPos = _monsterPos; }

    vector<Tile*> getTilesList() const { return TilesList; }
    vector<float> getMonsterPos() const { return monsterPos;}
    int getX();
    int getY();

};
#endif // _LEVEL_H_
