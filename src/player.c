// Copyright (c) Cyuria 2023, see LICENSE.txt for more information

#include "player.h"

player_s player;

const Hitbox playerhitbox = { 50, 50 };

// TODO: implement player movement
void move_player(int direction)
{

}

// TODO: implement collisions
void update_player_collisions(void)
{

}

// TODO: implement player updat
void update_player(float elapsedseconds)
{
  // Handle collisions

  // Move the player's position
  player.pos.x += elapsedseconds * player.velocity.x;
  player.pos.y += elapsedseconds * player.velocity.y;
}

// TODO: implement projectiles
void calc_player_hit(Projectile projectile)
{
  (void) projectile;
}

