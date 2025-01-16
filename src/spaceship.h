#pragma once

#include "vec2.h"
#include "game_object.h"
#include "atsin2d.h"

#include <fmt/core.h>

class Spaceship : public GameObject
{
public:
  Vec2 size;
  float speed;
  
  void load_resource(ResourceLoader * loader) override
  {
    _texture = loader->load_from_disk<SDL_Texture>("../bin/data/Game.png");
  }
  void init() override
  {
    size = {93,84};
    pos = {(Global::ScreenSize.x/2)-size.x,Global::ScreenSize.y-size.y};
    speed = 100.f;
  }
  void update(float delta) override
  {
    const bool* keystates = SDL_GetKeyboardState(NULL);
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
    SDL_FRect sprite_atlas = {120,604,104,84};
    SDL_FRect location = {pos.x, pos.y, size.x, size.y};
    //SDL_RenderTexture(renderer, _texture, &sprite_atlas,&location);
    SDL_RenderTextureRotated(renderer, _texture, &sprite_atlas,&location,0.0f,nullptr,SDL_FLIP_VERTICAL);
  }
private:
  SDL_Texture * _texture;
};
