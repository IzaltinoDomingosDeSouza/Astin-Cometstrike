#pragma once

#include "sdl2_backend.h"
#include "vec2.h"
#include "spaceship.h"
#include "atsin2d.h"

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
  
  //GameObject
  Spaceship _spaceship;
  
  void init()
  {
    _spaceship.init();
  }
  void update(float elapsed_time)
  {
    _spaceship.update(elapsed_time);
  }
  void draw()
  {
    _spaceship.draw(_backend.get_renderer());
  }
};
