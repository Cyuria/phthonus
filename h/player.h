// Copyright (c) Cyuria 2023, see LICENSE.txt for more information

#pragma once
#include "projectile.h"
#include "animation.h"

typedef struct {
  ivec2 pos;
  fvec2 velocity;
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
    int frametime;
    PlayerAnimation name;
    void (*finishanimation)(void);
  } animation;
  int blocking;
} player_s;
extern player_s player;

void move_player(int direction);

void update_player_collisions(void);

void update_player(float elapsedseconds);

void calc_player_hit(Projectile p);

void player_attack(fvec2 relmousepos);

void player_block_toggle(void);
void player_start_block(void);
void player_stop_block(void);
void player_finish_start_block(void);
void player_finish_stop_block(void);

void player_walk_reset_anim(void);

