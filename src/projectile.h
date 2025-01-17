#pragma once

#include "vec2.h"
#include "game_object.h"
#include "atsin2d.h"
#include "interface/box_collision.h"

class Projectile : public GameObject, public IBoxCollision
{
public:
  Vec2 size;
  float speed;
  
  Projectile(Vec2 position)
  {
    pos = position;
    size = {9,54};
    speed = 100.f;
    is_alive = true;
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
    
    update_shape();
  }
  void draw(SDL_Renderer * renderer) override
  {
    SDL_FRect sprite_atlas = {856,421,9,54};
    SDL_FRect location = {pos.x, pos.y, size.x, size.y};
    SDL_RenderTexture(renderer, _texture, &sprite_atlas,&location);
  }
  void update_shape() override
  {
    shape = {pos.x,pos.y,size.x,size.y};
  }
  void on_collition_with(GameObject * game_object) override
  {
    //fmt::print("On Collision with {}\n", to_string(game_object->tag_name));
    if(game_object->tag_name == TagName::TinyComet)
    {
      is_alive = false;
    }
  }
private:
  SDL_Texture * _texture;
};
