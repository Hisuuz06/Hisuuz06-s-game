#include "Level.h"

Level::Level(float _x, float _y, const char* _path, SDL_Texture* _tileTex)
    :x(_x), y(_y)
{
    //Success flag
    //bool tilesLoaded = true;

    //The tile offsets
    int x = getX(), y = getY();

    //Mở map
    ifstream map(_path);

    //Nếu ko đọc đc dữ liệu trong map
    if (map.fail()) {
        printf("Unable to load map file!\n");
        //tilesLoaded = false;
    }
    else
    {
        //Tạo các tile
        for (int i = 0; i < TOTAL_TILES; ++i) {
            //Chọn loại cho tile
            int tileType = -1;

            //Đọc từ map
            map >> tileType;

            //Debug
            if (map.fail()) {
                printf("Error loading map: Unexpected end of file!\n");
                //tilesLoaded = false;
                break;
            }

            //Nếu như đọc đc tileType và thỏa mãn
            if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES)) {
                Tile* tile = new Tile(x, y, _tileTex, tileType);
                TilesList.push_back(tile);
            }
            //Nếu như tileType ko thoả mãn
            else
            {
                printf("Error loading map: Invalid tile type at %d!\n", i);
                //tilesLoaded = false;
                break;
            }
            //Dịch x của tile tiếp theo
            x += TILE_WIDTH;

            //Nếu như đến giới hạn level
            if (x >= getX() + LEVEL_WIDTH) {
                //Xuống dòng mới và làm lại
                x = getX();
                y += TILE_HEIGHT;
            }
        }
    }
    map.close();
}

void Level::render(SDL_Rect _TileClips[], SDL_Rect& _camera )
{
    for(int i=0;i<TilesList.size();i++)
    {
        commonFunction::renderTile(*TilesList[i],_TileClips[TilesList[i]->getType()] ,_camera );
    }
}

void Level::setLevelX(Level& _level) {
    x = _level.getX() + LEVEL_WIDTH;
    for (int i = 0; i < TilesList.size(); i++) {
        int dong = i / 21;
        int cot = (i - dong * 21) * TILE_WIDTH + getX();
        TilesList[i]->setX(cot);
    }
}

void Level::setLevelX(float _x)
{
    x = _x;
    for (int i = 0; i < TilesList.size(); i++) {
        int dong = i / 21;
        int cot = (i - dong*21) * TILE_WIDTH + getX();
        TilesList[i]->setX(cot);
    }
}

void Level::setTilesType(const char* _path)
{
    bool tilesLoaded = true;
    int x = getX(), y = getY();
    ifstream map(_path);

    //Nếu ko đọc đc dữ liệu trong map
    if (map.fail()) {
        printf("Unable to load map file!\n");
        tilesLoaded = false;
    }
    else
    {
        //Tạo các tile
        for (int i = 0; i < TOTAL_TILES; ++i) {
            //Chọn loại cho tile
            int tileType = -1;

            //Đọc từ map
            map >> tileType;

            //Debug
            if (map.fail()) {
                printf("Error loading map: Unexpected end of file!\n");
                //tilesLoaded = false;
                break;
            }

            //Nếu như đọc đc tileType và thỏa mãn
            if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES)) {
                TilesList[i]->setType(tileType);

            }
            //Nếu như tileType ko thoả mãn
            else
            {
                printf("Error loading map: Invalid tile type at %d!\n", i);
                //tilesLoaded = false;
                break;
            }
            //Dịch x của tile tiếp theo
            x += TILE_WIDTH;

            //Nếu như đến giới hạn level
            if (x >= getX() + LEVEL_WIDTH) {
                //Xuống dòng mới và làm lại
                x = getX();
                y += TILE_HEIGHT;
            }
        }
    }
    map.close();
}


int Level::getX()
{
    return x;
}

int Level::getY()
{
    return y;
}
