// Copyright (c) Cyuria 2023, see LICENSE.txt for more information

#include "projectile.h"
#include <time.h>

Projectile create_projectile(
  const ivec2 pos,
  const Hitbox hb,
  const fvec2 velocity,
  const int damage,
  const dmg type,
  const clock_t duration)
{
  Projectile p = {
    .hitbox = hb,
    .pos = pos,
    .velocity = velocity,
    .damage = damage,
    .type = type
  };
  return p;
}

