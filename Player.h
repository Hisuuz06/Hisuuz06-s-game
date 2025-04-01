#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#include "window.h"
#include "Entity.h"
#include "Level.h"

class Player : public Entity
{
private:
    const int PLAYER_WIDTH = 64;
	const int PLAYER_HEIGHT = 64;
	const int PLAYER_VEL = 6;

	static const int WALKING_ANIMATION_FRAMES = 16;
	static const int IDLING_ANIMATION_FRAMES = 4;
	static const int JUMPING_ANIMATION_FRAMES = 8;
	static const int FALLING_ANIMATION_FRAMES = 4;
	static const int DEATH_ANIMATION_FRAMES = 4;

	SDL_Rect walkingClips[WALKING_ANIMATION_FRAMES];
	SDL_Rect idlingClips[IDLING_ANIMATION_FRAMES];
	SDL_Rect jumpingClips[JUMPING_ANIMATION_FRAMES];
	SDL_Rect fallingClips[FALLING_ANIMATION_FRAMES];
	SDL_Rect deathClips[DEATH_ANIMATION_FRAMES];

	int idleCounter = 0, walkCounter = 0, jumpCounter = 0, fallingCounter = 0, deathCounter = 0;
    bool grounded = false, running = false, idling = true, jumping = false, falling = true, dead = false, beingHit = false;	int groundSTT = 1;
	int levelSTT = 1;
	float xVel=0, yVel=0;
	SDL_Rect collision;
public:
    Player(float _x, float _y, SDL_Texture* _texture);
    void update(vector<Level>& LevelList, SDL_Rect& camera);
    void jump();
    void gravity();
    bool isDead() { return dead; }
    void handleInput(SDL_Event &events);
    void handleCamera(SDL_Rect& camera, float& camVel);
    void render(SDL_Rect& _camera);

    SDL_Rect getCollision();
};

#endif // _PLAYER_H_
