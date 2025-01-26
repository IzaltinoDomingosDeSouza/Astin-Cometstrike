#pragma once

#include "vec2.h"
#include "game_object.h"
#include "atsin2d.h"
#include "interface/create_projectile.h"
#include "interface/box_collision.h"
#include "interface/health.h"

#include <fmt/core.h>

class Spaceship : public GameObject, public ICreateProjectile, public IBoxCollision, public IHealth
{
public:
  Vec2 size;
  float speed;
  void init() override
  {
    size = {93,84};
    pos = {(Global::ScreenSize.x - size.x)/2,Global::ScreenSize.y-size.y};
    speed = 150.f;
    tag_name = TagName::Player;
    is_alive = true;
    max_health = 100;
    current_health = 100;
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
    
    if(keystates[SDL_SCANCODE_SPACE])
    {
        _should_fire = true;
    }
    _next_fire_time -= delta;
    if(_next_fire_time < 0.0f)
    {
      _next_fire_time = 0.0f;
    }
    
    if(_should_fire && _next_fire_time == 0.0f)
    {
      _next_fire_time = _fire_time_delay;
       _should_fire = true;
    }else
    {
      _should_fire = false; 
    }
    
    update_shape();
  }
  void draw(AtlasRenderer * atlas_renderer) override
  {
    SDL_FRect sprite_atlas = {120,604,104,84};
    SDL_FRect location = {pos.x, pos.y, size.x, size.y};
    atlas_renderer->draw(AtlasType::Game, &sprite_atlas, &location,TextureFlip::Vertical);
  }
  bool should_fire() override
  {
    return _should_fire;
  }
  Projectile * create_projectile() override
  {
    _should_fire = false;
    return new Projectile(Vec2{pos.x + (size.x / 2) - 5, pos.y-37});
  }
  void update_shape() override
  {
    shape = {pos.x,pos.y,size.x,size.y};
  }
  void on_collition_with(GameObject * game_object) override
  {
    //fmt::print("On Collision with {}\n", to_string(game_object->tag_name));
  }
private:
  bool _should_fire{false};
  float _next_fire_time{0.0f};
  float _fire_time_delay{0.25f};
};
