#pragma once

#include <SDL3/SDL.h>
#include <fmt/core.h>

class SDLBackend
{
public:
  SDLBackend()
  {
    if(!SDL_Init(SDL_INIT_VIDEO))
    {
      fmt::print("SDL could not initialize! SDL_Error : {}\n", SDL_GetError());
    }
  }
  ~SDLBackend()
  {
    if(!_renderer) SDL_DestroyRenderer(_renderer);
    if(!_window) SDL_DestroyWindow(_window);
    
    SDL_Quit();
  }
  bool init(const char * title,size_t width,size_t height,bool fullscreen = false)
  {
    _window = SDL_CreateWindow(title,
                              width, height,
                              fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE);
    if(!_window)
    {
        fmt::print("Window could not be created! SDL_Error: {}\n", SDL_GetError());
        SDL_Quit();
        return false;
    }
    _renderer = SDL_CreateRenderer(_window, nullptr);
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
  void get_window_size(float & width, float & height)
  {
    int w,h;
    SDL_GetWindowSize(_window,&w,&h);
    width = w;
    height = h;
  }
private:
  SDL_Window * _window = nullptr;
  SDL_Renderer * _renderer = nullptr;
};
