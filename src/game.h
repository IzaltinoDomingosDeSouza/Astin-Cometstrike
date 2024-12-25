#pragma once

#include "sdl2_backend.h"
#include "vec2.h"

class Game
{
public:
  Game()
  {
    if(!_backend.init("Atsin Comestrike",800,600,false))
    {
      fmt::print("SDL_Error : {}\n", SDL_GetError());
    }
  }
  void run()
  {
    init();
    
    _is_running = true;
    SDL_Event e;
    
    Uint32 elapsed_time = 0;
    while(_is_running)
    {
      Uint32 start_time = SDL_GetTicks();  // Record the start time
      int last_time = start_time;
      
      while (SDL_PollEvent(&e) != 0)
      {
        if(e.type == SDL_QUIT)
        {
          _is_running = false;
        }
      }
      
      update(elapsed_time / 1000.0f);
      draw();
      
      Uint32 current_time = SDL_GetTicks();
      elapsed_time = current_time - start_time;
    }
  }
private:
  SDL2Backend _backend;
  bool _is_running;
  
  //SpaceShip
  Vec2 _spaceship_pos = {0,0};
  Vec2 _spaceship_size = {256,256};
  float _spaceship_speed = 100.f;
  
  void init()
  {
  }
  void update(float elapsed_time)
  {
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    if(keystates[SDL_SCANCODE_RIGHT])
    {
      _spaceship_pos.x += _spaceship_speed * elapsed_time;
    }
    if(keystates[SDL_SCANCODE_LEFT])
    {
      _spaceship_pos.x -= _spaceship_speed * elapsed_time;
    }
  }
  void draw()
  {
    auto renderer = _backend.get_renderer();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_Rect fillRect = {(int)_spaceship_pos.x,(int)_spaceship_pos.y,
                         (int)_spaceship_size.x,(int)_spaceship_size.y};
    
    SDL_RenderFillRect(renderer, &fillRect);

    SDL_RenderPresent(renderer);
  }
};
