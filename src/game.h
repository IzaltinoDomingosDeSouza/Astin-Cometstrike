#pragma once

#include "sdl2_backend.h"

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
    
    while(_is_running)
    {
      while (SDL_PollEvent(&e) != 0)
      {
        if(e.type == SDL_QUIT)
        {
          _is_running = false;
        }
      }
      update();
      draw();
    }
  }
private:
  SDL2Backend _backend;
  bool _is_running;
  
  void init()
  {
  }
  void update()
  {
  
  }
  void draw()
  {
    auto renderer = _backend.get_renderer();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_Rect fillRect = {0, 0, 256, 256};
    SDL_RenderFillRect(renderer, &fillRect);

    SDL_RenderPresent(renderer);
  }
};
