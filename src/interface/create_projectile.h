#pragma once

#include "../projectile.h"

class ICreateProjectile
{
public:
    virtual bool should_fire() = 0;
    virtual Projectile * create_projectile() = 0;
};
