#ifndef _MONSTER_H_
#define _MONSTER_H_
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <math.h>

#include "window.h"
#include "Player.h"
#include "Entity.h"
#include "Level.h"
class Player;
using namespace std;
class Monster : public Entity
{
private:
    const int MONSTER_WIDTH = 64;
    const int MONSTER_HEIGHT = 64;
    const int MONSTER_VEL = 4;

    static const int WALKING_ANIMATION_FRAMES = 4;
	static const int IDLING_ANIMATION_FRAMES = 4;
	static const int FALLING_ANIMATION_FRAMES = 4;
	static const int BEINGHIT_ANIMATION_FRAMES = 4;
	SDL_Rect walkingClips[WALKING_ANIMATION_FRAMES];
	SDL_Rect fallingClips[FALLING_ANIMATION_FRAMES];
	SDL_Rect idlingClips[IDLING_ANIMATION_FRAMES];
	SDL_Rect beingHitClips[BEINGHIT_ANIMATION_FRAMES];
	int idleCounter = 0, fallingCounter = 0, walkCounter = 0, beingHitCounter = 0;
	bool grounded = true, walking = false, falling = false, idling = true, beingHit = false, dead = false;

	float xVel = 0, yVel = 0;
	int groundSTT = 1;
	int levelSTT = 1;
	float distanceToPlayer;
	SDL_Rect collision;
public:
    Monster(float _x, float _y, SDL_Texture* _texture);

    void update(Player& _player, vector<Level>& LevelList, SDL_Rect& camera);
    void gravity();
    void autoMovement(vector<Level>& LevelList);
    void moveToPlayer(Player& _player, vector<Level>& LevelList);
    bool isDead() { return dead; }
    void getHit(Player& _player, SDL_Rect& camera);
    void render(SDL_Rect& _camera);

    SDL_Rect getCollision() const { return collision; }
	float getDistance() { return distanceToPlayer; }
};
#endif // _MONSTER_H_
