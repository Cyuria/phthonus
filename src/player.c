// Copyright (c) Cyuria 2023, see LICENSE.txafor more information

#include "player.h"
#include <time.h>
#include "projectile.h"

player_s player;

const int playerdamage = 1;

const Hitbox playerhitbox = { 50, 50 };
const Hitbox attackhitbox = { 25, 10 };

// TODO: implement player movement
void move_player(int direction)
{
  (void) direction;
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

// TODO: implement attacking
void player_attack(const fvec2 relmousepos)
{
  const float length = fvec2_len(relmousepos);
  const fvec2 projvel = {
    .x = relmousepos.x / length,
    .y = relmousepos.y / length,
  };
  (void) projvel;
  //create_projectile(player.pos, attackhitbox, projvel, playerdamage, PHYSICAL, );
}

void player_block_toggle(void)
{
  if (player.blocking)
    player_stop_block();
  else
    player_start_block();
}
void player_start_block(void)
{
  player.animation.name = startblock;
  player.animation.frame = 0;
  player.animation.frametime = time(NULL);
  player.animation.finishanimation = &player_finish_start_block;
}
void player_finish_start_block(void)
{
  player.blocking = 1;
}
void player_stop_block(void)
{
  player.animation.name = stopblock;
  player.animation.frame = 0;
  player.animation.frametime = time(NULL);
  player.blocking = 0;
  player.animation.finishanimation = &player_finish_stop_block;
}
void player_finish_stop_block(void)
{
  player.animation.name = noanim;
  player.animation.frame = 0;
  player.animation.frametime = time(NULL);
}

void player_walk_reset_anim(void)
{
  player.animation.frame = 0;
  player.animation.frametime = time(NULL);
}

