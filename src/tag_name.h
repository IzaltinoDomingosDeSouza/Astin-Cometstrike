#pragma once

enum class TagName
{
  Undefined,
  Player,
  PlayerProjectile,
  TinyComet,
};

std::string to_string(TagName tag_name)
{
  switch(tag_name)
  {
    case TagName::Player:
      return "Player";
    break;
    case TagName::PlayerProjectile:
      return "PlayerProjectile";
    break;
    case TagName::TinyComet:
      return "TinyComet";
    break;
  }
  return "Undefined";
}
