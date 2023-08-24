
#include <stdio.h>

#include <SDL.h>

#include "tmp.h"

int SDL_main(int argc, char* argv[]) {
  (void) argc; (void) argv;

  printf("Hello, World! %d\n", add(1, 2));

  return 0;
}

