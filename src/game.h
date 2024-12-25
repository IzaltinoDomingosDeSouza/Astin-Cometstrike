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
    
    auto renderer = _backend.get_renderer();

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
      
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);
      draw();
      SDL_RenderPresent(renderer);
      
      Uint32 current_time = SDL_GetTicks();
      elapsed_time = current_time - start_time;
    }
  }
private:
  SDL2Backend _backend;
  bool _is_running;
  
  //SpaceShip
  Vec2 _spaceship_pos = {(800/2)-32,600-32};
  Vec2 _spaceship_size = {32,32};
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
    
    if(_spaceship_pos.x < 0)
    {
      _spaceship_pos.x =  0;
    }
    if(_spaceship_pos.x + _spaceship_size.x > 800)
    {
      _spaceship_pos.x = 800 - _spaceship_size.x;
    }
  }
  void draw()
  {
    auto renderer = _backend.get_renderer();

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_Rect fillRect = {(int)_spaceship_pos.x,(int)_spaceship_pos.y,
                         (int)_spaceship_size.x,(int)_spaceship_size.y};
    
    SDL_RenderFillRect(renderer, &fillRect);
  }
};
