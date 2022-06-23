#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <string>
#include "RenderWindow.h"
#include "Entity.h"
#include "Ball.h"	
#include "Tile.h"
#include "Hole.h"
#include "Hand.h"

using namespace std;
bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;
	if (!(TTF_Init()))
		std::cout << "TTF_init has failed. Error: " << SDL_GetError() << std::endl;
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	return true;
}

bool SDLinit = init();




RenderWindow window("Twini-Golf", 640, 480);

SDL_Texture* ballTexture = window.loadTexture("res/gfx/ball.png");
SDL_Texture* holeTexture = window.loadTexture("res/gfx/hole.png");
SDL_Texture* pointTexture = window.loadTexture("res/gfx/point.png");
SDL_Texture* tileDarkTexture32 = window.loadTexture("res/gfx/tile32_dark.png");
SDL_Texture* tileDarkTexture64 = window.loadTexture("res/gfx/tile64_dark.png");
SDL_Texture* tileLightTexture32 = window.loadTexture("res/gfx/tile32_light.png");
SDL_Texture* tileLightTexture64 = window.loadTexture("res/gfx/tile64_light.png");
SDL_Texture* ballShadowTexture = window.loadTexture("res/gfx/ball_shadow.png");
SDL_Texture* bgTexture = window.loadTexture("res/gfx/bg.png");
SDL_Texture* uiBgTexture = window.loadTexture("res/gfx/UI_bg.png");
SDL_Texture* levelTextBgTexture = window.loadTexture("res/gfx/levelText_bg.png");
SDL_Texture* powerMeterTexture_FG = window.loadTexture("res/gfx/powermeter_fg.png");
SDL_Texture* powerMeterTexture_BG = window.loadTexture("res/gfx/powermeter_bg.png");
SDL_Texture* powerMeterTexture_overlay = window.loadTexture("res/gfx/powermeter_overlay.png");
SDL_Texture* logoTexture = window.loadTexture("res/gfx/logo.png");
SDL_Texture* click2start = window.loadTexture("res/gfx/click2start.png");
SDL_Texture* endscreenOverlayTexture = window.loadTexture("res/gfx/end.png");
SDL_Texture* splashBgTexture = window.loadTexture("res/gfx/splashbg.png");


Mix_Chunk* chargeSfx = Mix_LoadWAV("res/sfx/charge.mp3");
Mix_Chunk* swingSfx = Mix_LoadWAV("res/sfx/swing.mp3");
Mix_Chunk* holeSfx = Mix_LoadWAV("res/sfx/hole.mp3");


SDL_Color white = { 255, 255, 255 };
SDL_Color black = { 0, 0, 0 };
TTF_Font* font32 = TTF_OpenFont("res/font/font.ttf", 32);
TTF_Font* font48 = TTF_OpenFont("res/font/font.ttf", 48);
TTF_Font* font24 = TTF_OpenFont("res/font/font.ttf", 24);

Ball balls[2] = {Ball(Vector2f(0, 0), ballTexture, pointTexture, powerMeterTexture_FG, powerMeterTexture_BG, 0), Ball(Vector2f(0, 0), ballTexture, pointTexture, powerMeterTexture_FG, powerMeterTexture_BG, 1) };
std::vector<Hole> holes = { Hole(Vector2f(0, 0), holeTexture), Hole(Vector2f(0, 0), holeTexture) };


std::vector<Tile> loadTiles(int level)
{
	std::vector<Tile> temp = {};
	switch (level)
	{
	case 0:

		temp.push_back(Tile(Vector2f(64 * 3, 64 * 3), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(64 * 4, 64 * 3), tileDarkTexture64));

		temp.push_back(Tile(Vector2f(64 * 0, 64 * 3), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(64 * 1, 64 * 3), tileDarkTexture64));

	

		temp.push_back(Tile(Vector2f(64 * 3 + 64 * 5, 64 * 3), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 4 + 64 * 5, 64 * 3), tileLightTexture64));

		temp.push_back(Tile(Vector2f(64 * 0 + 64 * 5, 64 * 3), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 1 + 64 * 5, 64 * 3), tileLightTexture64));
		break;
	case 1:
		temp.push_back(Tile(Vector2f(64 * 2, 64 * 3), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(64 * 3, 64 * 5), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(64 * 1, 64 * 3), tileDarkTexture64));



		temp.push_back(Tile(Vector2f(64 * 4 + 64 * 5, 64 * 3), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 0 + 64 * 4, 64 * 3), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 1 + 64 * 5, 64 * 2), tileLightTexture64));
		break;
	case 2:
		temp.push_back(Tile(Vector2f(64 * 3, 64 * 7), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(64 * 2, 64 * 5), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(32 * 3, 32 * 1), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 1, 32 * 3), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(64 * 5, 64 * 3), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(32 * 3, 32 * 5), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(64 * 7, 64 * 5), tileDarkTexture64));

		

		temp.push_back(Tile(Vector2f(32 * 1 + 32 * 10 + 16, 32 * 5), tileLightTexture32));
		temp.push_back(Tile(Vector2f(64 * 2 + 64 * 4, 64 * 3), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 4 + 32 * 8, 64 * 3), tileLightTexture64));
		temp.push_back(Tile(Vector2f(32 * 2 + 32 * 7, 32 * 2 + 32 * 1), tileLightTexture32));
		temp.push_back(Tile(Vector2f(64 * 5 + 64 * 8, 64 * 10), tileLightTexture64));
		break;
	case 3:
		temp.push_back(Tile(Vector2f(32 * 4, 32 * 7), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(32 * 3, 32 * 5), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 6, 32 * 3), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(32 * 3, 32 * 1), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 1, 32 * 3), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(32 * 5, 32 * 3), tileDarkTexture32));


		temp.push_back(Tile(Vector2f(32 * 4 + 64 * 5, 32 * 2), tileLightTexture64));
		temp.push_back(Tile(Vector2f(32 * 3 + 32 * 10, 32 * 6), tileLightTexture32));
		temp.push_back(Tile(Vector2f(32 * 6 + 32 * 10, 32 * 9), tileLightTexture32));
		temp.push_back(Tile(Vector2f(32 * 2 + 32 * 10, 32 * 2), tileLightTexture64));
		temp.push_back(Tile(Vector2f(32 * 5 + 32 * 10, 32 * 11), tileLightTexture64));
		temp.push_back(Tile(Vector2f(32 * 3 + 32 * 5, 32 * 1 + 32 * 2), tileLightTexture64));
		break;
	case 4:
		temp.push_back(Tile(Vector2f(32 * 3, 32 * 1), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(32 * 1, 32 * 3), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 5, 32 * 3), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(32 * 3, 32 * 5), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 7, 32 * 5), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(32 * 7, 32 * 10), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(32 * 3, 32 * 10), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 5, 32 * 12), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(32 * 7, 32 * 10), tileDarkTexture32));

	
		//temp.push_back(Tile(Vector2f(32*4, 32*7), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(486, 380), tileLightTexture64));

		temp.push_back(Tile(Vector2f(614, 330), tileLightTexture32));
		temp.push_back(Tile(Vector2f(527, 326), tileLightTexture32));

		temp.push_back(Tile(Vector2f(527, 440), tileLightTexture64));
		temp.push_back(Tile(Vector2f(32 * 8 + 32 * 10, 32 * 6), tileLightTexture64));
		temp.push_back(Tile(Vector2f(32 * 3 + 32 * 10, 32 * 11), tileLightTexture64));
		break;

	case 5:
		temp.push_back(Tile(Vector2f(32 * 2, 32 * 2), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(32 * 1, 32 * 3 ), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 3, 32 * 3 + 32 * 2), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(32 * 4, 32 * 5 + 32 * 1), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(32 * 6 + 32 * 1, 32 * 5), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 7, 32 * 10), tileDarkTexture32));

		temp.push_back(Tile(Vector2f(330, 220), tileLightTexture32));
		temp.push_back(Tile(Vector2f(480, 250), tileLightTexture32));



		temp.push_back(Tile(Vector2f(465, 355), tileLightTexture64));
		temp.push_back(Tile(Vector2f(420, 400), tileLightTexture64));
		temp.push_back(Tile(Vector2f(32 * 3 + 32 * 10, 32 * 11), tileLightTexture64));
		break;
	case 6:
		temp.push_back(Tile(Vector2f(32 * 2 + 25, 32 * 1), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 1 + 64 * 1, 32 * 3 + 20 * 2), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(32 * 5 + 32 * 1, 32 * 3), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 3 + 30, 32 * 5), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 4 + 32 * 1, 32 * 5 + 32), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(32 * 7, 32 * 10), tileDarkTexture64));

		temp.push_back(Tile(Vector2f(470, 300), tileLightTexture32));
		temp.push_back(Tile(Vector2f(430, 260), tileLightTexture32));

		

		temp.push_back(Tile(Vector2f(448, 176), tileLightTexture64));
		temp.push_back(Tile(Vector2f(525, 177), tileLightTexture64));
		temp.push_back(Tile(Vector2f(530, 274), tileLightTexture64));
		break;


	case 7:
		temp.push_back(Tile(Vector2f(32 * 2 + 25, 32 * 1), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(32 * 1 + 64 * 1, 32 * 3 + 20 * 2), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 5 + 32 * 1, 32 * 3), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(32 * 3 + 30, 32 * 5), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(32 * 4 + 32 * 1, 32 * 5 + 32), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 7, 32 * 10), tileDarkTexture32));

		temp.push_back(Tile(Vector2f(501, 315), tileLightTexture64));
		temp.push_back(Tile(Vector2f(501, 397), tileLightTexture64));



		temp.push_back(Tile(Vector2f(501, 456), tileLightTexture64));
		temp.push_back(Tile(Vector2f(450, 307), tileLightTexture64));
		temp.push_back(Tile(Vector2f(340, 315), tileLightTexture64));
		temp.push_back(Tile(Vector2f(443, 215), tileLightTexture32));
		break;
	}
	return temp;
}

int level = 0;
std::vector<Tile> tiles = loadTiles(level);

bool gameRunning = true;
bool mouseDown = false;
bool mousePressed = false;

bool swingPlayed = false;
bool secondSwingPlayed = false;


SDL_Event event;

int state = 0; //0 = title screen, 1 = game, 2 = end screen

Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double deltaTime = 0;

void loadLevel(int level)
{
	if (level > 7)
	{
		state = 2;
		return;
	}
	balls[0].setVelocity(0, 0);
	balls[1].setVelocity(0, 0);
	balls[0].setScale(1, 1);
	balls[1].setScale(1, 1);
	balls[0].setWin(false);
	balls[1].setWin(false);


	tiles = loadTiles(level);

	switch (level)
	{
	case 0:
		balls[0].setPos(24 + 32 * 4, 24 + 32 * 11);
		balls[1].setPos(24 + 32 * 4 + 32 * 10, 24 + 32 * 11);

		holes.at(0).setPos(24 + 32 * 4, 22 + 32 * 2);
		holes.at(1).setPos(24 + 32 * 4 + 32 * 10, 22 + 32 * 2);
	
		break;
	case 1:
		balls[0].setPos(24 + 32 * 4, 24 + 32 * 11);
		balls[1].setPos(24 + 32 * 4 + 32 * 10, 24 + 32 * 11);

		holes.at(0).setPos(24 + 32 * 4, 22 + 32 * 2);
		holes.at(1).setPos(24 + 32 * 4 + 32 * 7, 22 + 32 * 2);

		break;
	case 2:
		balls[0].setPos(8 + 32 * 7, 8 + 32 * 10);
		balls[1].setPos(8 + 32 * 7 + 32 * 10, 8 + 32 * 10);

		holes.at(0).setPos(8 + 32 * 2, 6 + 32 * 5);
		holes.at(1).setPos(8 + 32 * 4 + 32 * 10, 6 + 32 * 3);

		break;
	case 3:
		balls[0].setPos(24 + 32 * 4, 24 + 32 * 5);
		balls[1].setPos(24 + 32 * 4 + 32 * 10, 24 + 32 * 4);

		holes.at(0).setPos(24 + 32 * 4, 22 + 32 * 1);
		holes.at(1).setPos(30 + 32 * 5 + 32 * 10, 30 + 32 * 12);
		break;
	case 4:
		balls[0].setPos(24 + 32 * 2, 24 + 32 * 12);
		balls[1].setPos(580, 425);

		holes.at(0).setPos(24 + 32 * 1, 22 + 32 * 1);
		holes.at(1).setPos(24 + 32 * 0 + 32 * 10, 22 + 32 * 7);

		break;
	case 5:
		balls[0].setPos(26 + 32 * 2, 30 + 32 * 7);
		balls[1].setPos(470, 144);

		holes.at(0).setPos(20 + 32 * 2, 20 + 30);
		holes.at(1).setPos(24 + 32 * 10, 26 + 32 * 7);
		break;
	case 6:
		balls[0].setPos(140, 75);
		balls[1].setPos(24 + 32 * 4 + 32 * 10, 24 + 32 * 11);

		holes.at(0).setPos(24 + 32 * 4, 22 + 32 * 2);
		holes.at(1).setPos(24 + 32 * 4 + 32 * 10, 24*3 + 32 * 2);

		break;
	case 7:
		balls[0].setPos(24 + 32 * 4, 24 + 32 * 11);
		balls[1].setPos(600, 410);

		holes.at(0).setPos(24 + 32 * 4, 22 + 32 * 2);
		holes.at(1).setPos(390, 390);

		break;
	}
}


 
void get_text_and_rect(SDL_Renderer* renderer, int x, int y, char* text,TTF_Font* font, SDL_Texture** texture, SDL_Rect* rect) {
	int text_width;
	int text_height;
	SDL_Surface* surface;
	SDL_Color textColor = { 255, 255, 255, 0 };

	surface = TTF_RenderText_Solid(font, text, textColor);
	*texture = SDL_CreateTextureFromSurface(renderer, surface);
	text_width = surface->w;
	text_height = surface->h;
	SDL_FreeSurface(surface);
	rect->x = x;
	rect->y = y;
	rect->w = text_width;
	rect->h = text_height;
}

void update()
{
	bool inside;
	SDL_Rect SpriteCLips[35];
	SDL_Rect current = SpriteCLips[28];
	SDL_Rect quadrad = { 10, 10, 50, 50 };
	lastTick = currentTick;
	currentTick = SDL_GetPerformanceCounter();
	deltaTime = (double)((currentTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency());

	
	mousePressed = false;
	
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			gameRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				mouseDown = true;
				mousePressed = true;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				mouseDown = false;
			}
			break;
		}
		if (event.type == SDL_MOUSEMOTION)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);

			inside = true;
			if (x < 10 || x > 50 || y < 10 || y > 50) inside = false;

			if (inside == true) current = SpriteCLips[29];
			else current = SpriteCLips[28];
		}

		
	}
	/*
	int angle = 0;
	int s = 30;
	it->loadTextures("res/gfx/hand.png", window.takerenderer());
	it->setScale(s, s);
	it->draw(angle,window.takerenderer());
	angle++;
	SDL_Delay(200);
	*/
	if (state == 1)
	{
		for (Ball& b : balls)
		{
			b.update(deltaTime, mouseDown, mousePressed, tiles, holes, chargeSfx, swingSfx, holeSfx);
		
		}
		 if(balls[0].getScale().x < -1 && balls[1].getScale().x < -1)
		{

			level++;
			loadLevel(level);
		}
	
	
	}

	
}

void graphics()
{
	window.clear();
	window.render(0, 0, bgTexture);
	for (Hole& h : holes)
	{
		window.render(h);
	}
	for (Ball& b : balls)
	{
		if (!b.isWin())
		{
			window.render(b.getPos().x, b.getPos().y + 4, ballShadowTexture);
		}
		for (Entity& e : b.getPoints())
		{
			window.render(e);
		}
		window.render(b);
	}
	for (Tile& t : tiles)
	{
		window.render(t);
	}
	for (Ball& b : balls)
	{
		for (Entity& e : b.getPowerBar())
		{
			window.render(e);
		}
		window.render(b.getPowerBar().at(0).getPos().x, b.getPowerBar().at(0).getPos().y, powerMeterTexture_overlay);

	}
	
	
	if (state != 2)
	{
		window.render(640 / 4 - 132 / 2, 480 - 32, levelTextBgTexture);
		window.renderCenter(-160, 240 - 16 + 3, "HOLE 1", font24, black);
		window.renderCenter(-160, 240 - 16, "HOLE 1", font24, white);

		window.render(640 / 2 + 640 / 4 - 132 / 2, 480 - 32, levelTextBgTexture);
		window.renderCenter(160, 240 - 16 + 3,"HOLE 2", font24, black);
		window.renderCenter(160, 240 - 16, "HOLE 2", font24, white);

		
		
	}
	else
	{
		window.render(0, 0, endscreenOverlayTexture);
		window.renderCenter(0, 3 - 32, "YOU COMPLETED THE COURSE!", font48, black);
		window.renderCenter(0, -32, "YOU COMPLETED THE COURSE!", font48, white);

	}
	window.display();
}

void titleScreen()
{
	if (SDL_GetTicks() < 2000)
	{
		if (!swingPlayed)
		{
			Mix_PlayChannel(-1, swingSfx, 0);
			swingPlayed = true;
		}
		//Get our controls and events
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				gameRunning = false;
				break;
			}
		}

		window.clear();
		window.render(0, 0, bgTexture);
		window.render(0, 0, splashBgTexture);
		window.renderCenter(0, 0 + 3, "MY 2D GAME", font32, black);
		window.renderCenter(0, 0, "MY 2D GAME", font32, white);
		window.display();
	}
	else
	{
		if (!secondSwingPlayed)
		{
			Mix_PlayChannel(-1, swingSfx, 0);
			secondSwingPlayed = true;
		}
		lastTick = currentTick;
		currentTick = SDL_GetPerformanceCounter();
		deltaTime = (double)((currentTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency());

		//Get our controls and events
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				gameRunning = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					Mix_PlayChannel(-1, holeSfx, 0);
					state = 1;
				}
				break;
			}
		}
		window.clear();
		window.render(0, 0, bgTexture);
		window.render(320 - 160, 240 - 100 - 50 + 4 * SDL_sin(SDL_GetTicks() * (3.14 / 1500)), logoTexture);
		window.render(0, 0, click2start);
		window.renderCenter(0, 240 - 48 + 3 - 16 * 5, "LEFT CLICK TO START", font32, black);
		window.renderCenter(0, 240 - 48 - 16 * 5, "LEFT CLICK TO START", font32, white);
		window.display();
	}
}
void game()
{
	if (state == 0)
	{
		titleScreen();
	}
	else
	{
		update();
		graphics();
	}
}

int main(int argc, char* args[])
{
	SDL_Renderer* renderer;
	loadLevel(level);
	while (gameRunning)
	{
		game();

	}

	window.cleanUp();
	TTF_CloseFont(font32);
	TTF_CloseFont(font24);
	SDL_Quit();
	TTF_Quit();
	return 0;
}