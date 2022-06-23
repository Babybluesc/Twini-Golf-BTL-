#include<iostream>
#include<SDL.h>
#include<string>
#include<SDL_image.h>
#include <SDL_ttf.h>

#include "Hole.h"
#include "Hand.h"
#include "Entity.h"
#include "Ball.h"
#include <Math.h>

/*
Hand::Hand(Vector2f p_pos, SDL_Texture* p_tex) 
{
    mPos.x = p_pos.x;
    mPos.y = p_pos.y;
    mRotation = 0.0f;
    mParent = NULL;
    mScale = Vector_One;
}


void Hand::Pos(Vector2f pos)
{
    mPos = pos;
}

Vector2f Hand::Pos(SPACE space)
{
    if (space == local || mParent == NULL)
        return mPos;
    Vector2f parentScale = mParent->Scale(world);
   //Vector2f rotPos = RotateVector(mPos, mParent->Rotation(world));
  //  return mParent->Pos(world) + Vector2f(rotPos.x * parentScale.x, rotPos.y * parentScale.y);
}

void Hand::Rotation(float r)
{
    mRotation = r;
    if (mRotation > 360.0f)
        mRotation -= 360.0f;

    if (mRotation < 0.0f)
        mRotation += 360.0f;
}

double Hand::Rotation(SPACE space)
{
    if (space == local || mParent == NULL)
        return mRotation;
    return mParent->Rotation(world) + mRotation;
}

void Hand::Scale(Vector2f scale)
{
    mScale = scale;
}

Vector2f Hand::Scale(SPACE space)
{
    if (space == local || mParent == NULL)
        return mScale;
    Vector2f parentScale = mParent->Scale(world);
    return Vector2f(parentScale.x * mScale.x, parentScale.y * mScale.y);
}

void Hand::Rotate(float amount)
{
    mRotation += amount;
}
*/
/*void Hand::DrawTexture(SDL_Texture* tex, SDL_Rect* clip, SDL_Rect* rend, float angle, SDL_RendererFlip flip)
{
   
    //SDL_Surface* image = IMG_Load(path.c_str());
    //SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Point* holes = holes;
    Vector2f pos = Pos(world);
    Vector2f scale = Scale(world);

    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w=scale.x;
    src.h= scale.y;

    SDL_Rect dst;
    dst.x = (int)(pos.x - src.w * scale.x * 0.5f);
    dst.y = (int)(pos.y - src.h * scale.x * 0.5f);
    dst.w = (int)(src.w * scale.x);
    dst.h = (int)(src.h * scale.y);
    SDL_RenderCopyEx(renderer, tex, NULL, &dst, Rotation(world), NULL, SDL_FLIP_NONE);
}
*/
/*void Hand::Block(double deltaTime, bool mouseDown, bool mousePressed, std::vector<Tile> tiles, std::vector<Ball> balls)
{
   for(Ball& b: balls)
   {
    if (mousePressed && canMove)
    {
        
        int mouseX = 0;
        int mouseY = 0;
        SDL_GetMouseState(&mouseX, &mouseY);
        setInitialMousePos(mouseX, mouseY);
    }
    if (mouseDown && canMove)
    {

        int mouseX = 0;
        int mouseY = 0;
        SDL_GetMouseState(&mouseX, &mouseY);
        setVelocity((mouseX - getInitialMousePos().x) / -150, (mouseY - getInitialMousePos().y) / -150);
        setLaunchedVelocity((mouseX - getInitialMousePos().x) / -150, (mouseY - getInitialMousePos().y) / -150);
        velocity1D = SDL_sqrt(SDL_pow(abs(getVelocity().x), 2) + SDL_pow(abs(getVelocity().y), 2));
        launchedVelocity1D = velocity1D;

        points.at(0).setPos(getPos().x, getPos().y + 8 - 32);
        points.at(0).setAngle(SDL_atan2(velocity.y, velocity.x) * (180 / 3.1415) + 90);

        dirX = velocity.x / abs(velocity.x);
        dirY = velocity.y / abs(velocity.y);

 
        if (velocity1D > 1)
        {
            velocity1D = 1;
            launchedVelocity1D = 1;
        }
      
    }
    else
    {

        canMove = false;
        setPos(getPos().x + getVelocity().x * deltaTime, getPos().y + getVelocity().y * deltaTime);
        if (getVelocity().x > 0.0001 || getVelocity().x < -0.0001 || getVelocity().y > 0.0001 || getVelocity().y < -0.0001)
        {
            //float xDir = velocity.x/abs(velocity.x);
            //float yDir = velocity.y/abs(velocity.y);

            //velocity.x = (abs(velocity.x) - friction*deltaTime)*xDir;
            //velocity.y = (abs(velocity.y) - friction*deltaTime)*yDir;
            if (velocity1D > 0)
            {
                velocity1D -= friction * deltaTime;
            }
            else
            {
                velocity1D = 0;
            }
            velocity.x = (velocity1D / launchedVelocity1D) * abs(launchedVelocity.x) * dirX;
            velocity.y = (velocity1D / launchedVelocity1D) * abs(launchedVelocity.y) * dirY;


        }
        else
        {
            setVelocity(0, 0);
            int mouseX = 0;
            int mouseY = 0;
            SDL_GetMouseState(&mouseX, &mouseY);
            setInitialMousePos(mouseX, mouseY);
            canMove = true;
        }

        if (getPos().x + getCurrentFrame().w > 640 / (2 - index))
        {
            setVelocity(-abs(getVelocity().x), getVelocity().y);
            dirX = -1;
        }
        else if (getPos().x < 0 + (index * 320))
        {
            setVelocity(abs(getVelocity().x), getVelocity().y);
            dirX = 1;
        }
        else if (getPos().y + getCurrentFrame().h > 480)
        {
            setVelocity(getVelocity().x, -abs(getVelocity().y));
            dirY = -1;
        }
        else if (getPos().y < 0)
        {
            setVelocity(getVelocity().x, abs(getVelocity().y));
            dirY = 1;
        }
    }

    for (Tile& t : tiles)
    {
        float newX = getPos().x + getVelocity().x * deltaTime;
        float newY = getPos().y;
        if (newX + 16 > t.getPos().x && newX < t.getPos().x + t.getCurrentFrame().w && newY + 16 > t.getPos().y && newY < t.getPos().y + t.getCurrentFrame().h - 3)
        {
            setVelocity(getVelocity().x * -1, getVelocity().y);
            dirX *= -1;
        }

        newX = getPos().x;
        newY = getPos().y + getVelocity().y * deltaTime;
        if (newX + 16 > t.getPos().x && newX < t.getPos().x + t.getCurrentFrame().w && newY + 16 > t.getPos().y && newY < t.getPos().y + t.getCurrentFrame().h - 3)
        {
            setVelocity(getVelocity().x, getVelocity().y * -1);
            dirY *= -1;
        }
    }
}*/

Hand::Hand(Vector2f p_pos, SDL_Texture* p_tex)
    :Entity(p_pos, p_tex)
{
}