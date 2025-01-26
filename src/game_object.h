#pragma once

#include "atlas_renderer.h"
#include "tag_name.h"

class GameObject
{
public:
  Vec2 pos;
  TagName tag_name;
  bool is_alive;
  
  virtual void init() = 0;
  virtual void update(float delta) = 0;
  virtual void draw(AtlasRenderer * renderer) = 0;
  
  template <typename Interface>
  Interface * GetInterface()
  {
    return dynamic_cast<Interface*>(this);
  }
};
