#include "vec2.h"

namespace Global
{
  Vec2 ScreenSize;
  void KeepInsideOfScreen(Vec2 & position,Vec2 size,Vec2 screen_size = ScreenSize)
  {
    //UP AND DOWN
    if(position.y < 0)
    {
      position.y = 0;
    }
    if(position.y + size.y > screen_size.y)
    {
      position.y = screen_size.y - size.y;
    }
    
    //LEFT AND RIGHT
    if(position.x < 0)
    {
      position.x = 0;
    }
    if(position.x + size.x > screen_size.x)
    {
      position.x = screen_size.x - size.x;
    }
  }
  void ScreenWrap(Vec2 & position,Vec2 size,Vec2 screen_size = ScreenSize)
  {
    //UP AND DOWN
    if(position.y < 0)
    {
      position.y = screen_size.y - size.y;
    }
    if(position.y> screen_size.y)
    {
      position.y = 0;
    }
  
    //LEFT AND RIGHT
    if(position.x < 0)
    {
      position.x = screen_size.x - size.x;
    }
    if(position.x> screen_size.x)
    {
      position.x = 0;
    }
  }
}
