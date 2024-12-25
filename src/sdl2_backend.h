#pragma once

#include <SDL2/SDL.h>
#include <fmt/core.h>

class SDL2Backend
{
public:
  SDL2Backend()
  {
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
      fmt::print("SDL could not initialize! SDL_Error : {}\n", SDL_GetError());
    }
  }
  ~SDL2Backend()
  {
    if(!_renderer) SDL_DestroyRenderer(_renderer);
    if(!_window) SDL_DestroyWindow(_window);
    
    SDL_Quit();
  }
  bool init(const char * title,size_t width,size_t height,bool fullscreen = false)
  {
    _window = SDL_CreateWindow(title,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width, height,
                              fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN);
    if(!_window)
    {
        fmt::print("Window could not be created! SDL_Error: {}\n", SDL_GetError());
        SDL_Quit();
        return false;
    }
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if(!_renderer)
    {
        fmt::print("Renderer could not be created! SDL_Error : {}\n", SDL_GetError());
        SDL_DestroyWindow(_window);
        SDL_Quit();
        return false;
    }
    return true;
  }
  SDL_Renderer * get_renderer()
  {
    return _renderer;
  }
private:
  SDL_Window * _window = nullptr;
  SDL_Renderer * _renderer = nullptr;
};
