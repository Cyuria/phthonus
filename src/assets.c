// Copyright (c) Cyuria 2023, see LICENSE.txt for more information

#include "assets.h"
#include "utils.h"

int loadBMP(SDL_Surface** image, const char* filename)
{
  *image = NULL;
  *image = SDL_LoadBMP(filename);
  if (*image == NULL)
    return printerr(
      "SDL Failed to load image \"%s\", error: %s\n",
      SDL_GetError(), -1
    );
  return 0;
}

