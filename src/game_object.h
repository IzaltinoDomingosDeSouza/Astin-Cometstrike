#pragma once

#include "resource_loader.h"
#include "tag_name.h"

class GameObject
{
public:
  Vec2 pos;
  TagName tag_name;
  
  virtual void load_resource(ResourceLoader * loader) = 0;
  virtual void init() = 0;
  virtual void update(float delta) = 0;
  virtual void draw(SDL_Renderer * renderer) = 0;
  
  template <typename Interface>
  Interface * GetInterface()
  {
    return dynamic_cast<Interface*>(this);
  }
};
