#pragma once

class IBoxCollision
{
public:
    SDL_FRect shape;
    virtual void update_shape() = 0;
    bool collide_with(const SDL_FRect & other_shape) const
    {
      const bool horizontal_overlap = shape.x < other_shape.x + other_shape.w && shape.x + shape.w > other_shape.x;
      const bool vertical_overlap   = shape.y < other_shape.y + other_shape.h && shape.y + shape.h > other_shape.y;
      return horizontal_overlap && vertical_overlap;
    }
};
