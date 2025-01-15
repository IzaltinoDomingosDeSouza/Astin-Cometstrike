#pragma once

class GameObject
{
public:
  Vec2 pos;
  
  virtual void init() = 0;
  virtual void update(float delta) = 0;
  virtual void draw(SDL_Renderer * renderer) = 0;
};
