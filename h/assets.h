// Copyright (c) Cyuria 2023, see LICENSE.txt for more information

#pragma once
#include <sdl/SDL.h>

typedef enum {
  player_resting,
  player_floatingup,
  player_floatingdown,
  player_walk_left,
  player_walk_right,
  player_jump,
  player_land
} playertextures;
typedef enum {
  projectile_playerattack,
  projectile_fireball
} projectiletextures;

typedef struct {
  struct {
    SDL_Texture* resting[3];
    SDL_Texture* floatingup[3];
    SDL_Texture* floatingdown[3];
    SDL_Texture* walkleft[5];
    SDL_Texture* walkright[5];
    SDL_Texture* jump[4];
    SDL_Texture* land[7];
    SDL_Texture* attack[15];
  } player;
  struct {
    SDL_Texture* playerattack[15];
    SDL_Texture* fireball[10];
  } projectile;
} textures_s;
extern textures_s textures;

int loadBMP(SDL_Renderer*, SDL_Texture**, const char*);

SDL_Texture** getTexture(void* texstruct, size_t texid);

int loadAllTextures(SDL_Renderer* renderer);
int loadPlayerTextures(SDL_Renderer*);
int loadProjectileTextures(SDL_Renderer*);

