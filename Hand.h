#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <SDL_mixer.h>

#include "Math.h"
#include "Entity.h"
#include "Tile.h"
#include "Ball.h"
//Texture wrapper class
/*
class Hand
{
public:
    enum SPACE {local =0, world =1};
   
private:
    SDL_Renderer* renderer;
    Vector2f mPos;
    float mRotation;
    Vector2f mScale;
    Hand* mParent;
public:
    Hand(Vector2f p_pos, SDL_Texture* p_tex);
    
    void Pos(Vector2f pos);
    Vector2f Pos(SPACE space = world);

    void Rotation(float rotation);
    double Rotation(SPACE space = world);

    void Scale(Vector2f scale);
    Vector2f Scale(SPACE space = world);

    void Parent(Hand* parent);
    Hand* Parent();

    void Rotate(float amount);
   // void DrawTexture(SDL_Texture* tex, SDL_Rect* clip = NULL, SDL_Rect* rend = NULL, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
   // void Block(double DeltaTime, bool mouseDown, bool mousePressed, std::vector<Tile> tiles);
private:
    Hand();
    

};
*/

class Hand : public Entity
{
public:
    Hand(Vector2f p_pos, SDL_Texture* p_tex);

private:
};