#include "Menu.h"

Menu::Menu(SDL_Texture* _buttonTex, SDL_Texture* _mainMenuBGTex)
{
	for (int i = 0; i < TYPE_OF_BUTTON; i++) {
		playButtonClips[i].x = i * BUTTON_WIDTH;
		playButtonClips[i].y = 0;
		playButtonClips[i].w = BUTTON_WIDTH;
		playButtonClips[i].h = BUTTON_HEIGHT;

		exitButtonClips[i].x = i * BUTTON_WIDTH;
		exitButtonClips[i].y = BUTTON_HEIGHT;
		exitButtonClips[i].w = BUTTON_WIDTH;
		exitButtonClips[i].h = BUTTON_HEIGHT;

		retryButtonClips[i].x = i * BUTTON_WIDTH;
		retryButtonClips[i].y = BUTTON_HEIGHT * 2;
		retryButtonClips[i].w = BUTTON_WIDTH;
		retryButtonClips[i].h = BUTTON_HEIGHT;
	}
	buttonTex = _buttonTex;
	mainMenuBGTex = _mainMenuBGTex;
}

void Menu::handleInput(SDL_Event& event, bool& _gameRunning, Player& _player)
{
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT)
            {
			if (isMenu())
			{
				if (checkMouseHover(button1.x, button1.y)) {
					pressed[0] = true;
					menu = false;
				}
				if (checkMouseHover(button2.x, button2.y)) {
					pressed[1] = true;
					_gameRunning = false;
				}
			}
			if (_player.isDead()) {
				if (checkMouseHover(button1.x, button1.y)) {
					pressed[2] = true;
					reset = true;
				}
				if (checkMouseHover(button2.x, button2.y)) {
					pressed[3] = true;
					_gameRunning = false;
				}
			}
		}
		break;
	case SDL_MOUSEBUTTONUP:
		for (int i = 0; i < 4; i++) pressed[i] = false;
		break;
	case SDL_MOUSEMOTION:
		if (isMenu()) {
			if (checkMouseHover(button1.x, button1.y) && !pressed[0]) selected[0] = true;
			else selected[0] = false;
			if (checkMouseHover(button2.x, button2.y) && !pressed[1]) selected[1] = true;
			else selected[1] = false;
		}
		if (_player.isDead()) {
			if (checkMouseHover(button1.x, button1.y) && !pressed[2]) selected[2] = true;
			else selected[2] = false;
			if (checkMouseHover(button2.x, button2.y) && !pressed[3]) selected[3] = true;
			else selected[3] = false;
		}
		break;
	case SDL_KEYDOWN:
		if (event.key.repeat == 0) switch (event.key.keysym.sym) {
		case SDLK_ESCAPE:
			if (!paused) paused = true;
			else paused = false;
		}
	default:
		break;
	}
}

void Menu::renderMainMenu() {
	if (isMenu()) {
		commonFunction::renderTexture(mainMenuBGTex, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		if (selected[0]) commonFunction::renderTexture(buttonTex, button1.x, button1.y, 0, 0, &playButtonClips[1]);
		else commonFunction::renderTexture(buttonTex, button1.x, button1.y, 0, 0, &playButtonClips[0]);

		if (selected[1]) commonFunction::renderTexture(buttonTex, button2.x, button2.y, 0, 0, &exitButtonClips[1]);
		else commonFunction::renderTexture(buttonTex, button2.x, button2.y, 0, 0, &exitButtonClips[0]);
	}
}

void Menu::renderRetryMenu() {
	if (selected[2]) commonFunction::renderTexture(buttonTex, button1.x, button1.y, 0, 0, &retryButtonClips[1]);
	else commonFunction::renderTexture(buttonTex, button1.x, button1.y, 0, 0, &retryButtonClips[0]);

	if (selected[3]) commonFunction::renderTexture(buttonTex, button2.x, button2.y, 0, 0, &exitButtonClips[1]);
	else  commonFunction::renderTexture(buttonTex, button2.x, button2.y, 0, 0, &exitButtonClips[0]);
}

bool Menu::checkMouseHover(const int _x, const int _y) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x >= _x && y >= _y && x <= _x + BUTTON_WIDTH && y <= _y + BUTTON_HEIGHT) return true;
	return false;
}
