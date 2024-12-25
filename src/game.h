#pragma once

#include "sdl2_backend.h"
#include "vec2.h"
#include "spaceship.h"

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
  Spaceship _spaceship;
  
  void init()
  {
  }
  void update(float elapsed_time)
  {
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    if(keystates[SDL_SCANCODE_RIGHT])
    {
      _spaceship.pos.x += _spaceship.speed * elapsed_time;
    }
    if(keystates[SDL_SCANCODE_LEFT])
    {
      _spaceship.pos.x -= _spaceship.speed * elapsed_time;
    }
    
    if(_spaceship.pos.x < 0)
    {
      _spaceship.pos.x =  0;
    }
    if(_spaceship.pos.x + _spaceship.size.x > 800)
    {
      _spaceship.pos.x = 800 - _spaceship.size.x;
    }
  }
  void draw()
  {
    auto renderer = _backend.get_renderer();

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_Rect fillRect = {(int)_spaceship.pos.x,(int)_spaceship.pos.y,
                         (int)_spaceship.size.x,(int)_spaceship.size.y};
    
    SDL_RenderFillRect(renderer, &fillRect);
  }
};
