#pragma once

#include <SDL3_image/SDL_image.h>

class ResourceLoader
{
public:
  void init(SDL_Renderer * renderer)
  {
    _renderer = renderer;
  }
  template <typename T>
  T * load_from_disk(std::string path)
  {
    if constexpr (std::is_same<T, SDL_Texture>::value)
    {
      return IMG_LoadTexture(_renderer, path.c_str());
    }
  }
private:
  SDL_Renderer * _renderer = nullptr;
};
