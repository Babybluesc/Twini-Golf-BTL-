#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include<string>

#include "Entity.h"
#include "Hand.h"

class RenderWindow
{
public:
	RenderWindow(const char* p_title, int p_w, int p_);
	SDL_Texture* loadTexture(const char* p_filePath);
	//bool loadTextures(std::string path);
	void cleanUp();
	void clear();
	void render(Entity& p_entity);
	void render(Hand& hands);
	void render(int x, int y, SDL_Texture* p_tex);
	void render(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor);
	void renderCenter(float p_x, float p_y,const char* p_text, TTF_Font* font, SDL_Color textColor);
	void renderHand(std::string path);
	void display();
	/*SDL_Renderer* takerenderer() {
		return renderer;
	};*/
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};
