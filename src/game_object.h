#pragma once

#include "resource_loader.h"

class GameObject
{
public:
  Vec2 pos;
  
  virtual void load_resource(ResourceLoader * loader) = 0;
  virtual void init() = 0;
  virtual void update(float delta) = 0;
  virtual void draw(SDL_Renderer * renderer) = 0;
};
