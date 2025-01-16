#pragma once

#include "vec2.h"
#include "game_object.h"
#include "atsin2d.h"

class Projectile : public GameObject
{
public:
  Vec2 size;
  float speed;
  
  Projectile(Vec2 position)
  {
    pos = position;
    size = {9,54};
    speed = 100.f;
  }
  void load_resource(ResourceLoader * loader) override
  {
    _texture = loader->load_from_disk<SDL_Texture>("../bin/data/Game.png");
  }
  void init() override
  {
    
  }
  void update(float delta) override
  {
    pos.y -= speed * delta;
  }
  void draw(SDL_Renderer * renderer) override
  {
    SDL_FRect sprite_atlas = {856,421,9,54};
    SDL_FRect location = {pos.x, pos.y, size.x, size.y};
    SDL_RenderTexture(renderer, _texture, &sprite_atlas,&location);
  }
private:
  SDL_Texture * _texture;
};
