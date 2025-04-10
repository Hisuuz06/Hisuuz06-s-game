#include "Player.h"

Player::Player(float _x, float _y, SDL_Texture* _texture) : Entity(_x,_y,_texture)
{
    collision.x=getX()+(PLAYER_WIDTH/2);
    collision.y=getY()+PLAYER_HEIGHT-20;
    collision.w=PLAYER_WIDTH;
    collision.h=PLAYER_HEIGHT;

    for (int i = 0; i < IDLING_ANIMATION_FRAMES; i++)
    {
		idlingClips[i].x = i * (getCurrentFrame().w/4);
		idlingClips[i].y = 0;
		idlingClips[i].w = getCurrentFrame().w/4;
		idlingClips[i].h = getCurrentFrame().h/9;
	}
	for (int i = 0; i < WALKING_ANIMATION_FRAMES; i++)
    {
        if(i<WALKING_ANIMATION_FRAMES&&i>=12)
        {
            walkingClips[i].x = (i-12) * (getCurrentFrame().w/4);
            walkingClips[i].y = (getCurrentFrame().h/9)*4;
        }
        else if( i<12&& i>=8)
        {
            walkingClips[i].x = (i-8) * (getCurrentFrame().w/4);
            walkingClips[i].y = (getCurrentFrame().h/9)*3;
        }
		else if (i<8 && i >= 4)
		{
			walkingClips[i].x = (i-4) * (getCurrentFrame().w/4);
			walkingClips[i].y = (getCurrentFrame().h/9)*2;
		}
		else
        {
            walkingClips[i].x = i * (getCurrentFrame().w/4);
            walkingClips[i].y = getCurrentFrame().h/9;
        }
		walkingClips[i].w = getCurrentFrame().w/4;
		walkingClips[i].h = getCurrentFrame().h/9;
	}
	for (int i = 0; i < JUMPING_ANIMATION_FRAMES; i++) {
        jumpingClips[i].x = i * (getCurrentFrame().w / 4);
        jumpingClips[i].y = (getCurrentFrame().h/9) * 5;
		jumpingClips[i].w = getCurrentFrame().w / 4;
		jumpingClips[i].h = getCurrentFrame().h / 9;
	}

	for (int i = 0; i < FALLING_ANIMATION_FRAMES; i++) {
		fallingClips[i].x = i * (getCurrentFrame().w / 4);
		fallingClips[i].y = (getCurrentFrame().h / 9) * 6;
		fallingClips[i].w = getCurrentFrame().w / 4;
		fallingClips[i].h = getCurrentFrame().h / 9;
	}
	for (int i = 0; i < DEATH_ANIMATION_FRAMES; i++)
    {
		deathClips[i].x = i * (getCurrentFrame().w / 4);
		deathClips[i].y = (getCurrentFrame().h / 9) * 8;
		deathClips[i].w = getCurrentFrame().w / 4;
		deathClips[i].h = getCurrentFrame().h / 9;
	}

}

void Player::handleInput(SDL_Event &events)
{
    if (!isDead()) {
        if(events.type == SDL_KEYDOWN && events.key.repeat==0)
        {
            switch (events.key.keysym.sym)
            {
            case SDLK_RIGHT:
                xVel+=PLAYER_VEL;
                break;
            case SDLK_LEFT:
                xVel-=PLAYER_VEL;
                break;
            case SDLK_SPACE:
                if(grounded){
                    jump();
                }
                break;
            default:
                break;
            }
        }
        else if(events.type == SDL_KEYUP && events.key.repeat==0)
        {
            switch (events.key.keysym.sym)
            {
            case SDLK_RIGHT:
                xVel-=PLAYER_VEL;
                break;
            case SDLK_LEFT:
                xVel+=PLAYER_VEL;
                break;
            case SDLK_SPACE:
                if(!grounded&&jumping){
                    yVel *= 0.5f;
                }
                break;
            default:
                break;
            }
        }
    }
}

void Player::jump()
{
	if (grounded) {
		yVel -= 10;
		grounded = false;
	}
}

void Player::gravity()
{
	if (!grounded) {
		yVel += GRAVITY;
		if (yVel > MAX_GRAVITY) yVel = MAX_GRAVITY;
	}
	else yVel = GRAVITY;
}


void Player::update(vector<Level>& LevelList, SDL_Rect& camera) {
	gravity();

	// set trạng thái Player
	if (xVel == 0 && grounded && !dead) idling = true;
	else idling = false;

	if (xVel != 0 && grounded && !dead) running = true;
	else running = false;

	if (yVel > 0 && !grounded && !dead) falling = true;
	else falling = false;

	if (yVel <= 0 && !grounded && !dead) jumping = true;
	else jumping = false;


	if (!beingHit) {
		if (xVel < 0) flipType = SDL_FLIP_HORIZONTAL;
		if (xVel > 0) flipType = SDL_FLIP_NONE;
	}

	//move x
	if (!dead) {
		x += xVel;
		collision.x = getX() + PLAYER_WIDTH/2;

		if (getX() + PLAYER_WIDTH < 0) {
			x = -PLAYER_WIDTH;
			collision.x = getX() + PLAYER_WIDTH/2;
		}
		if (commonFunction::touchesWall(collision, LevelList)) {
			x -= xVel;
			collision.x = getX() + PLAYER_WIDTH/2;
		}
	}

	//move y
	y += yVel;
	collision.y = getY() + PLAYER_HEIGHT-20;
	if (getY() + PLAYER_HEIGHT < 0) {
		y = -PLAYER_HEIGHT;
		collision.y = getY() + PLAYER_HEIGHT-20;
	}
	if (commonFunction::touchesWall(collision, LevelList, grounded, groundSTT, levelSTT)) {
		if (yVel > 0) {
			y = LevelList[levelSTT].getTilesList()[groundSTT]->getY() - 64 * 2+20;
			if (falling) {
				grounded = true;
			}
		}
		else if (yVel < 0) {
			y -= yVel;
			yVel = 0;
		}
		collision.y = getY() + PLAYER_HEIGHT-20;
	}
}

void Player::handleCamera(SDL_Rect& camera, float& camVel)
{
    //if(!isDead()) camera.x += camVel;
    //float giatoc= 0.001;
    //if (camVel > 4) giatoc = 0.0003;
	//if (camVel > 5) giatoc = 0.00001;
	//camVel+=giatoc;
	if (getX() + PLAYER_WIDTH / 2 - camera.x >= SCREEN_WIDTH * 2 / 3)
    {
		camera.x = (getX() + PLAYER_WIDTH / 2) - SCREEN_WIDTH * 2 / 3;
	}
	camera.y = (getY() + PLAYER_HEIGHT / 2) - SCREEN_HEIGHT / 2;
	if (camera.x < 0)
    {
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.y > LEVEL_HEIGHT - camera.h)
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}

void Player::render(SDL_Rect &_camera)
{
    if(running)
    {
        commonFunction::renderAnimation(texture, x, y, walkingClips[walkCounter/4],_camera,0,NULL,getFlipType());
        walkCounter++;
        if (walkCounter/4 >= WALKING_ANIMATION_FRAMES) walkCounter = 0;
    }
    if (idling) {
		commonFunction::renderAnimation(texture, x, y, idlingClips[idleCounter/6], _camera, 0, NULL, getFlipType());
		idleCounter++;
		if (idleCounter / 6 >= IDLING_ANIMATION_FRAMES) idleCounter = 0;
	}
	else idleCounter = 0;

	if (jumping) {
		commonFunction::renderAnimation(texture, x, y, jumpingClips[jumpCounter / 5], _camera, 0, NULL, getFlipType());
		jumpCounter++;
		if (jumpCounter / 5 >= JUMPING_ANIMATION_FRAMES) jumpCounter = 0;
	}
	else jumpCounter = 0;

    if (falling) {
		commonFunction::renderAnimation(texture, x, y, fallingClips[fallingCounter / 4], _camera, 0, NULL, getFlipType());
		fallingCounter++;
		if (fallingCounter / 4 >= FALLING_ANIMATION_FRAMES) fallingCounter = 0;
	}
	else fallingCounter = 0;

	if (dead) {
		commonFunction::renderAnimation(texture, x, y, deathClips[deathCounter / 5], _camera, 0, NULL, getFlipType());
		if(deathCounter / 5 < DEATH_ANIMATION_FRAMES-1) deathCounter++;
	}
	else deathCounter = 0;
}
