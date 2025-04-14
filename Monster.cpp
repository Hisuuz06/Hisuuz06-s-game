#include "Monster.h"

Monster::Monster(float _x, float _y, SDL_Texture* _texture) : Entity(_x, _y, _texture)
{
    collision.x = getX() + (getCurrentFrame().w/4 - MONSTER_WIDTH)/2;
    collision.y = getY() + (getCurrentFrame().h/3 - MONSTER_HEIGHT);
    collision.w = MONSTER_WIDTH;
    collision.h = MONSTER_HEIGHT;

    for (int i = 0; i < WALKING_ANIMATION_FRAMES; i++) {
		walkingClips[i].x = i * (getCurrentFrame().w / 4);
		walkingClips[i].y = getCurrentFrame().h / 3;
		walkingClips[i].w = getCurrentFrame().w / 4;
		walkingClips[i].h = getCurrentFrame().h / 3;
	}
	for (int i = 0; i < IDLING_ANIMATION_FRAMES; i++) {
		idlingClips[i].x = i * (getCurrentFrame().w / 4);
		idlingClips[i].y = 0;
		idlingClips[i].w = getCurrentFrame().w / 4;
		idlingClips[i].h = getCurrentFrame().h / 3;
	}
	for (int i = 0; i < FALLING_ANIMATION_FRAMES; i++) {
		fallingClips[i].x = i * (getCurrentFrame().w / 4);
		fallingClips[i].y = 0;
		fallingClips[i].w = getCurrentFrame().w / 4;
		fallingClips[i].h = getCurrentFrame().h / 3;
	}
	for (int i = 0; i < BEINGHIT_ANIMATION_FRAMES; i++) {
		beingHitClips[i].x = i * (getCurrentFrame().w / 4);
		beingHitClips[i].y = (getCurrentFrame().h / 3) * 2;
		beingHitClips[i].w = getCurrentFrame().w / 4;
		beingHitClips[i].h = getCurrentFrame().h / 3;
	}
}

void Monster::update(Player& _player, vector<Level>& LevelList, Mix_Chunk* _sfx, SDL_Rect& camera) {
	if (!beingHit) {
		if (xVel < 0) flipType = SDL_FLIP_HORIZONTAL;
		if (xVel > 0) flipType = SDL_FLIP_NONE;
	}
	gravity();
	getHit(_player, _sfx, camera);
	autoMovement(LevelList);
	moveToPlayer(_player, LevelList);

	if (xVel == 0 && grounded  && !dead && !beingHit) idling = true;
	else idling = false;

	if (xVel != 0 && grounded  && !dead && !beingHit) walking = true;
	else walking = false;

	if (yVel > 0 && !grounded && !dead && !beingHit) falling = true;
	else falling = false;

	//move x
	x += xVel;
    collision.x = getX() + (getCurrentFrame().w/4 - MONSTER_WIDTH)/2;

    if (getX() + (getCurrentFrame().w/4 - MONSTER_WIDTH)/2 < 0) {
        x = - (getCurrentFrame().w/4 - MONSTER_WIDTH)/2;
        collision.x = getX() + (getCurrentFrame().w/4 - MONSTER_WIDTH)/2;
        xVel *= -1;
    }
    if (commonFunction::touchesWall(collision, LevelList)) {
        x -= xVel;
        collision.x = getX() + (getCurrentFrame().w/4 - MONSTER_WIDTH)/2;
        xVel *= -1;
    }

    y += yVel;
    collision.y = getY() + (getCurrentFrame().h/3 - MONSTER_HEIGHT);
    if (getY() + (getCurrentFrame().h/3 - MONSTER_HEIGHT)<0){
        y = -(getCurrentFrame().h/3 - MONSTER_HEIGHT);
        collision.y = getY() + (getCurrentFrame().h/3 - MONSTER_HEIGHT);
    }

    if (commonFunction::touchesWall(collision, LevelList, grounded, groundSTT, levelSTT)){
        if(yVel>0){
            y = LevelList[levelSTT].getTilesList()[groundSTT]->getY()- getCurrentFrame().h/3;
            if (falling){
            grounded = true;
            }
        }
        else if(yVel<0){
            y-= yVel;
            yVel=0;
        }
        collision.y = getY() + (getCurrentFrame().h/3 - MONSTER_HEIGHT);
    }
}
void Monster::gravity() {
	if (!grounded) {
		yVel += GRAVITY;
		if (yVel > MAX_GRAVITY) yVel = MAX_GRAVITY;
	}
	else yVel = GRAVITY;
}

void Monster::autoMovement(vector<Level>& LevelList)
{
    if(!beingHit){
        if (LevelList[levelSTT].getTilesList()[groundSTT + 1]->getType() > MAX_TILE && LevelList[levelSTT].getTilesList()[groundSTT - 1]->getType() > MAX_TILE) xVel = 0;
        else if (LevelList[levelSTT].getTilesList()[groundSTT + 1]->getType() > MAX_TILE && xVel > 0) xVel = -MONSTER_VEL * 0.5;
        else if (LevelList[levelSTT].getTilesList()[groundSTT - 1]->getType() > MAX_TILE && xVel < 0) xVel = MONSTER_VEL * 0.5;
        else if(getFlipType() == SDL_FLIP_NONE) xVel = MONSTER_VEL * 0.5;
		else if(getFlipType() == SDL_FLIP_HORIZONTAL) xVel = -MONSTER_VEL * 0.5;
    }
}

void Monster::moveToPlayer(Player& _player, vector<Level>& LevelList)
{
    distanceToPlayer = sqrt(pow(_player.getX() - getX(), 2) + pow(_player.getY() - getY(), 2));
    if (!beingHit){
        if(distanceToPlayer<=7*TILE_WIDTH){
            if(_player.getX() - getX() <0 ){
                if (LevelList[levelSTT].getTilesList()[groundSTT - 1]->getType() > MAX_TILE) xVel = 0;
				else xVel = -MONSTER_VEL;
            }
            else if (LevelList[levelSTT].getTilesList()[groundSTT + 1]->getType() > MAX_TILE) xVel = 0;
			else xVel = MONSTER_VEL;
        }
    }
}

void Monster::getHit(Player& _player, Mix_Chunk* _sfx, SDL_Rect& camera)
{
    bool check = false;
    if(commonFunction::checkCollision(_player.getCollision(),collision)){
        if(_player.isFalling()){
            check = true;
            beingHit = true;
        }
    }
    if (beingHitCounter / 7 >= BEINGHIT_ANIMATION_FRAMES) {
		beingHit = false;
		beingHitCounter = 0;
	}
	if(check||getY()+MONSTER_HEIGHT/2>LEVEL_HEIGHT||getX()-camera.x<0){
        dead = true;
        beingHit = false;
        Mix_PlayChannel(-1,_sfx,0);
	}
}

void Monster::render(SDL_Rect& _camera) {
	if (walking) {
		commonFunction::renderAnimation(texture, x, y, walkingClips[walkCounter / 4], _camera, 0, NULL, getFlipType());
		walkCounter++;
		if (walkCounter / 4 >= WALKING_ANIMATION_FRAMES) walkCounter = 0;
	}

	if (idling) {
		commonFunction::renderAnimation(texture, x, y, idlingClips[idleCounter / 6], _camera, 0, NULL, getFlipType());
		idleCounter++;
		if (idleCounter / 6 >= IDLING_ANIMATION_FRAMES) idleCounter = 0;
	}
	else idleCounter = 0;

	if (falling) {
		commonFunction::renderAnimation(texture, x, y, fallingClips[fallingCounter / 4], _camera, 0, NULL, getFlipType());
		fallingCounter++;
		if (fallingCounter / 4 >= FALLING_ANIMATION_FRAMES) fallingCounter = 0;
	}
	else fallingCounter = 0;

	if (beingHit) {
		commonFunction::renderAnimation(texture, x, y, beingHitClips[beingHitCounter / 7], _camera, 0, NULL, getFlipType());
		beingHitCounter++;
	}
	else beingHitCounter = 0;
}

