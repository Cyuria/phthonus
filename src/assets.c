// Copyright (c) Cyuria 2023, see LICENSE.txt for more information

#include "assets.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sdl/SDL.h>
#include "sdl/SDL_error.h"
#include "utils.h"

textures_s textures;

SDL_Texture** getTexture(void* texstruct, size_t texid)
{
  return *(((SDL_Texture***) texstruct) + texid);
}

int loadBMP(SDL_Renderer* renderer, SDL_Texture** texture, const char* filename)
{
  printf("filename given to load: %s\n", filename);
  *texture = NULL;
  SDL_Surface* image = NULL;
  image = SDL_LoadBMP(filename);
  if (image == NULL)
    return printerr(
      "SDL Failed to load image \"%s\", error: %s\n",
      SDL_GetError(), -1
    );
  *texture = SDL_CreateTextureFromSurface(renderer, image);
  if (*texture == NULL)
      return printerr(
        "Could not create texture for player resting animation: %s\n",
        SDL_GetError(), -1
      );
  return 0;
}

int loadTexturesFromBMPs(
  SDL_Renderer* renderer,
  SDL_Texture** textureloc,
  const char* filenameproto,
  int num)
{
  assert(num < 100000); // require num to have less than 6 digits
  char* fname = malloc(strlen(filenameproto) + 5);
  for (int i = 0; i < num; i++) {
    sprintf(fname, filenameproto, i);
    int error = loadBMP(renderer, &(textureloc[i]), fname);
    if (error)
    {
      free(fname);
      return error;
    }
  }
  free(fname);
  return 0;
}

int loadAllTextures(SDL_Renderer* renderer)
{
  int error = 0;

  error = loadPlayerTextures(renderer);
  if (error) return error;
  error = loadProjectileTextures(renderer);
  if (error) return error;

  return 0;
}

#define guardedloadtexcall(texloc, fnameproto) \
{ \
  int error = loadTexturesFromBMPs( \
    renderer, (texloc), (fnameproto), \
    sizeof(texloc) / sizeof((texloc)[0]) \
  ); \
  if (error) return error; \
}

int loadPlayerTextures(SDL_Renderer* renderer)
{
  guardedloadtexcall(
    textures.player.resting,
    "assets/player/resting/%d.bmp"
  )
  guardedloadtexcall(
    textures.player.floatingup,
    "assets/player/floatingup/%d.bmp"
  )
  guardedloadtexcall(
    textures.player.floatingdown,
    "assets/player/floatingdown/%d.bmp"
  )
  guardedloadtexcall(
    textures.player.walkleft,
    "assets/player/walkleft/%d.bmp"
  )
  guardedloadtexcall(
    textures.player.walkright,
    "assets/player/walkright/%d.bmp"
  )
  guardedloadtexcall(
    textures.player.jump,
    "assets/player/jump/%d.bmp"
  )

  return 0;
}
int loadProjectileTextures(SDL_Renderer* renderer)
{
  guardedloadtexcall(
    textures.projectile.playerattack,
    "assets/projectile/playerattack/%d.bmp"
  )
  guardedloadtexcall(
    textures.projectile.fireball,
    "assets/projectile/fireball/%d.bmp"
  )

  return 0;
}

#undef guardedloadtexcall

