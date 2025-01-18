#pragma once

class IHealth
{
public:
    float max_health;
    float current_health;
    void take_damage(float amount)
    {
      current_health -= amount;
      if(current_health <= 0.0f)
      {
        current_health = 0.0f;
      }
    }
    void heal(float amount)
    {
      current_health += amount;
      if(current_health >= max_health)
      {
        current_health = max_health;
      }
    }
};
