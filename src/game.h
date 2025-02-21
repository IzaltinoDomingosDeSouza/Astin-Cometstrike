#pragma once

#include "sdl_backend.h"
#include "vec2.h"
#include "spaceship.h"
#include "tiny_comet.h"
#include "atsin2d.h"
#include "atlas_renderer.h"
#include "collision_system.h"
#include "comet_wave_system.h"
#include "background.h"

#include <vector>
#include <algorithm>

class Game
{
public:
  Game()
  {
    Global::ScreenSize = {800,600};
    if(!_backend.init("Atsin Comestrike",Global::ScreenSize.x,Global::ScreenSize.y,false))
    {
      fmt::print("SDL_Error : {}\n", SDL_GetError());
    }
  }
  void run()
  {
    init();
    
    _is_running = true;
    SDL_Event e;
    
    auto renderer = _backend.get_renderer();
    

    Uint32 elapsed_time = 0;
    while(_is_running)
    {
      Uint32 start_time = SDL_GetTicks();
      int last_time = start_time;
      
      while (SDL_PollEvent(&e) != 0)
      {
        if(e.type == SDL_EVENT_QUIT)
        {
          _is_running = false;
        }else if(e.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED)
        {
          _backend.get_window_size(Global::ScreenSize.x,Global::ScreenSize.y);
        }
      }
      
      update(elapsed_time / 1000.0f);
      
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);
      draw();
      SDL_RenderPresent(renderer);
      
      Uint32 current_time = SDL_GetTicks();
      elapsed_time = current_time - start_time;
    }
  }
private:
  SDLBackend _backend;
  AtlasRenderer _atlas_renderer;
  CollisionSystem _collision_system;
  CometWaveSystem _comet_wave_system;
  Background _background;
  bool _is_running;
  
  std::vector<GameObject*> _game_objects;
  
  void init()
  {
    auto renderer = _backend.get_renderer();
    _atlas_renderer.init(renderer);
    _background.init();
    _comet_wave_system.init();

    _game_objects.push_back(new Spaceship);
    for(auto & game_object : _game_objects)
    {
      game_object->init();
    }
    
    _collision_system.init();
  }
  void update(float elapsed_time)
  {
    _background.update(elapsed_time);

    auto add_game_objects = std::vector<GameObject*>();
    auto remove_game_objects = std::vector<GameObject*>();
  
    for(auto & game_object : _game_objects)
    {
      game_object->update(elapsed_time);

      if(auto interface = game_object->GetInterface<ICreateProjectile>())
      {
        if(interface->should_fire())
        {
          auto projectile = interface->create_projectile();
          projectile->init();
          projectile->tag_name = TagName::PlayerProjectile;
          add_game_objects.push_back(projectile);
        }
      }
    }
    
    _collision_system.update(_game_objects);
    _comet_wave_system.update(elapsed_time,&add_game_objects);
    
    for(auto & game_object : add_game_objects)
    {
      _game_objects.push_back(game_object);
    }

    for(auto & game_object : _game_objects)
    {
      if(!game_object->is_alive)
      {
        remove_game_objects.push_back(game_object);
      }
    }
    for(auto & game_object : remove_game_objects)
    {
      auto it = std::find(_game_objects.begin(), _game_objects.end(), game_object);
      if(it != _game_objects.end())
      {
        _game_objects.erase(it);
      }
    }
  }
  void draw()
  {
    _background.draw(&_atlas_renderer);
    for(auto & game_object : _game_objects)
    {
      game_object->draw(&_atlas_renderer);
    }
  }
};
