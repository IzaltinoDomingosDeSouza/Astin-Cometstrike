#pragma once

#include <vector>
#include <random>

#include "atsin2d.h"
#include "tiny_comet.h"

class CometWaveSystem
{
public:
  void init()
  {
    _max_comet_per_wave = 5;
    _next_wave_time = 2.0;
    _countdown = _next_wave_time;
    
    std::random_device rd;
    _random_gen = std::mt19937(rd());
    _distribution_x = std::uniform_real_distribution<float>(100.0f, Global::ScreenSize.x - 100.0f);
    _distribution_y = std::uniform_real_distribution<float>(-100.0f, 0.f);
  }
  void update(float delta_time,std::vector<GameObject*> * game_objects)
  {
    _countdown -= delta_time;
    if(_countdown <= 0.0)
    {
      for(int comet_per_wave = 0;comet_per_wave < _max_comet_per_wave; ++comet_per_wave)
      {
        game_objects->push_back(new TinyComet(Vec2{_distribution_x(_random_gen),_distribution_y(_random_gen)}));
      }
      _countdown = _next_wave_time;
    }
  }
private:
  float _max_comet_per_wave;
  float _next_wave_time;
  float _countdown;
  std::mt19937 _random_gen;
  std::uniform_real_distribution<float> _distribution_x;
  std::uniform_real_distribution<float> _distribution_y;
};
