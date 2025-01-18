#pragma once

#include "vec2.h"
#include "game_object.h"
#include "atsin2d.h"
#include "interface/box_collision.h"
#include "interface/health.h"

class TinyComet : public GameObject, public IBoxCollision, public IHealth
{
public:
  Vec2 size;
  float speed;
  int health;
  
  TinyComet(Vec2 position)
  {
    pos = position;
    size = {18,18};
    speed = 120.f;
    tag_name = TagName::TinyComet;
    is_alive = true;
    max_health = 100;
    current_health = 100;
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
    pos.y += speed * delta;
    update_shape();

    if(pos.y > Global::ScreenSize.y)
    {
      is_alive = false;
    }
    if(current_health == 0)
    {
      is_alive = false;
    }
  }
  void draw(SDL_Renderer * renderer) override
  {
    SDL_FRect sprite_atlas = {346,814,18,18};
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
    if(game_object->tag_name == TagName::PlayerProjectile)
    {
      take_damage(100);
      fmt::print("On Collision with {} health {} \n", to_string(game_object->tag_name),health);
    }
    else if(game_object->tag_name == TagName::Player)
    {
      take_damage(100);
      auto interface = game_object->GetInterface<IHealth>();
      if(interface)
      {
        interface->take_damage(10);
      }
    }
  }
private:
  SDL_Texture * _texture;
};
