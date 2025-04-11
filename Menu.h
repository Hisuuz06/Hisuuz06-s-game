#ifndef _MENU_H_
#define _MENU_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>

#include "window.h"
#include "Entity.h"
#include "Player.h"
#include "Timer.h"
using namespace std;

class Menu
{
private:
    const int BUTTON_WIDTH = 80;
	const int BUTTON_HEIGHT = 83;
	static const int TYPE_OF_BUTTON = 2;
	SDL_Rect playButtonClips[TYPE_OF_BUTTON];
	SDL_Rect exitButtonClips[TYPE_OF_BUTTON];
	SDL_Rect retryButtonClips[TYPE_OF_BUTTON];

	SDL_Point button1 = { SCREEN_WIDTH/2 - BUTTON_WIDTH/2, SCREEN_HEIGHT/2 };
	SDL_Point button2 = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT/2 + BUTTON_HEIGHT + 32 };

	bool menu = true, retry = false, paused = false, reset = false;
	bool selected[4] = { false };
	bool pressed[4] = { false };

	SDL_Texture* buttonTex = NULL;
	SDL_Texture* mainMenuBGTex = NULL;
public:
    Menu(SDL_Texture* buttonTex, SDL_Texture* mainMenuBGTex);
	void handleInput(SDL_Event& event, bool& _gameRunning, Player& _player);
	void renderMainMenu();
	void renderRetryMenu();
	bool checkMouseHover(const int x, const int y);
	bool isMenu() const { return menu; }
	bool isPaused() const { return paused; }
	bool need_reseting() const { return reset; }
	void set_reset(bool _reset) { reset = _reset; }
};
#endif // _MENU_H_
