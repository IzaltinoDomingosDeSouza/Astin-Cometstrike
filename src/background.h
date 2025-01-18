#pragma once

#include "vec2.h"
#include "game_object.h"
#include "atsin2d.h"

class Background
{
public:
  
  void load_resource(ResourceLoader * loader)
  {
    _texture = loader->load_from_disk<SDL_Texture>("../bin/data/Background/DarkPurple.png");
  }
  void init()
  {
    _pos = Vec2{0,0};
    _size = Vec2{256,256};
    _speed = 100;
  }
  void update(float delta)
  {
    _pos.y += _speed * delta;
    if(_pos.y >= 0.0f)
    {
      _pos.y = -_size.y;
    }
  }
  void draw(SDL_Renderer * renderer)
  {
    for(float y = _pos.y; y < Global::ScreenSize.y; y += _size.y)
    {
      for(float x = _pos.x; x < Global::ScreenSize.x; x += _size.x)
      {
        SDL_FRect location = {x,y, _size.x, _size.y};
        SDL_RenderTexture(renderer, _texture, nullptr,&location);
      }
    }
  }
private:
  SDL_Texture * _texture;
  Vec2 _pos;
  Vec2 _size;
  float _speed;
};
