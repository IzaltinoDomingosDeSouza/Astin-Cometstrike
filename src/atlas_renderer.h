#pragma once

#include <SDL3_image/SDL_image.h>

enum class AtlasType
{
  Background = 0,
  Game = 1,
  Menu = 2
};
enum class TextureFlip
{
  None = 0,
  Horizontal = 1,
  Vertical = 2
};

class AtlasRenderer
{
public:
  void init(SDL_Renderer * renderer)
  {
    _renderer = renderer;
  
    _texture[static_cast<int>(AtlasType::Background)] = IMG_LoadTexture(_renderer, "../bin/data/Background.png");
    _texture[static_cast<int>(AtlasType::Game)] = IMG_LoadTexture(_renderer, "../bin/data/Game.png");
  }
  SDL_Texture * get_texture(AtlasType type)
  {
    return _texture[static_cast<int>(type)];
  }
  void draw(const AtlasType type, const SDL_FRect * sprite_atlas, const SDL_FRect * screen_location)
  {
    SDL_RenderTexture(_renderer, _texture[static_cast<int>(type)], sprite_atlas,screen_location);
  }
  void draw(const AtlasType type, const SDL_FRect * sprite_atlas, const SDL_FRect * screen_location,TextureFlip flip)
  {
    SDL_RenderTextureRotated(_renderer, _texture[static_cast<int>(type)],
                            sprite_atlas,screen_location,
                            0.0f,nullptr,static_cast<SDL_FlipMode>(flip));
  }
private:
  SDL_Renderer * _renderer = nullptr;
  SDL_Texture * _texture[3];
};
