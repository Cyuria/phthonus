// Copyright (c) Cyuria 2023, see LICENSE.txt for more information

#pragma once
#include <time.h>
#include "assets.h"
#include "utils.h"

typedef enum { PHYSICAL, MAGIC, SOUL, TRUE } dmg;

typedef struct {
  int w;
  int h;
} Hitbox;

typedef struct {
  Hitbox hitbox;
  ivec2 pos;
  fvec2 velocity;
  int damage;
  dmg type;
  int deathtime;
} Projectile;

Projectile create_projectile(
  const ivec2 pos,
  const Hitbox hb,
  const fvec2 velocity,
  const int damage,
  const dmg type,
  const clock_t duration);

