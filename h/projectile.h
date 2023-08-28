// Copyright (c) Cyuria 2023, see LICENSE.txt for more information

#pragma once
#include "projectile.h"

enum dmg { PHYSICAL, MAGIC, SOUL, TRUE };

struct hitbox_s {
  int w;
  int h;
};
typedef struct hitbox_s Hitbox;

struct projectile_s {
  Hitbox hitbox;
  struct {
    int x;
    int y;
  } pos;
  struct {
    float x;
    float y;
  } speed;
  int damage;
  enum dmg dmgtype;
};
typedef struct projectile_s Projectile;

Projectile create_projectile(int, int, int, int, float, float, int, enum dmg);

