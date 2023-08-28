// Copyright (c) Cyuria 2023, see LICENSE.txt for more information

#pragma once
#include "projectile.h"

#include "animation.h"

typedef struct {
  struct {
    int x;
    int y;
  } pos;
  struct {
    float x;
    float y;
  } velocity;
  struct {
    int health;
    int mana;
    float speed;
  } stats;
  struct {
    int health;
    int mana;
    float speed;
    int armour;
  } upgrades;
  struct {
    int health;
    int mana;
    float speed;
    int armour;
  } current;
  struct {
    int frame;
    int stoptime;
    PlayerAnimation name;
  } animation;
} player_s;
extern player_s player;

void move_player(int);

void update_player_collisions(void);

void update_player(float);

void calc_player_hit(Projectile);

void player_spawn_attack(void);

void player_block(void);

