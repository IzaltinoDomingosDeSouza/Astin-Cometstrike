#pragma once

#include "sdl_backend.h"
#include "vec2.h"
#include "spaceship.h"
#include "atsin2d.h"
#include "resource_loader.h"

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
    
    load_resource();
    
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
  ResourceLoader resource_loader;
  bool _is_running;
  
  std::vector<GameObject*> _game_objects;
  
  void load_resource()
  {
    auto renderer = _backend.get_renderer();
    resource_loader.init(renderer);
    for(auto & game_object : _game_objects)
    {
      game_object->load_resource(&resource_loader);
    }
  }
  
  void init()
  {
    _game_objects.push_back(new Spaceship);
    for(auto & game_object : _game_objects)
    {
      game_object->init();
    }
  }
  void update(float elapsed_time)
  {
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
          projectile->load_resource(&resource_loader);
          add_game_objects.push_back(projectile);
        }
      }
    }
    for(auto & game_object : add_game_objects)
    {
      _game_objects.push_back(game_object);
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
    for(auto & game_object : _game_objects)
    {
      game_object->draw(_backend.get_renderer());
    }
  }
};
