#pragma once

#include <vector>
#include "interface/box_collision.h"

class CollisionSystem
{
public:
  void init()
  {
    
  }
  void update(std::vector<GameObject*> game_objects)
  {
    for(auto & g_obj1 : game_objects)
    {
      for(auto & g_obj2 : game_objects)
      {
        auto i_gobj1 = g_obj1->GetInterface<IBoxCollision>();
        auto i_gobj2 = g_obj2->GetInterface<IBoxCollision>();
        if(g_obj1 != g_obj2 && i_gobj1 && i_gobj2 && i_gobj1->collide_with(i_gobj2->shape))
        {
          i_gobj1->on_collition_with(g_obj2);
        }
      }
    }
  }
};
