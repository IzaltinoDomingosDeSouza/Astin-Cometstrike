#pragma once

#include "vec2.h"
#include "game_object.h"
#include "atsin2d.h"

class Spaceship : public GameObject
{
public:
  Vec2 size;
  float speed;
  
  void init() override
  {
    pos = {(Global::ScreenSize.x/2)-32,Global::ScreenSize.y-32};
    size = {32,32};
    speed = 100.f;
  }
  void update(float delta) override
  {
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    if(keystates[SDL_SCANCODE_RIGHT])
    {
      pos.x += speed * delta;
    }
    if(keystates[SDL_SCANCODE_LEFT])
    {
      pos.x -= speed * delta;
    }

    Global::KeepInsideOfScreen(pos,size);
  }
  void draw(SDL_Renderer * renderer) override
  {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
    SDL_Rect spaceship = {(int)pos.x,(int)pos.y,
                         (int)size.x,(int)size.y};
    
    SDL_RenderFillRect(renderer, &spaceship);
  }
};
