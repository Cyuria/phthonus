// Copyright (c) Cyuria 2023, see LICENSE.txt for more information

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sdl/SDL.h>

#include "assets.h"
#include "player.h"
#include "settings.h"
#include "system.h"
#include "utils.h"

static int init_SDL(void);
static int close_SDL(void);

static int init_gamestate(void);

static void draw(void);
static void loop(void);
static void event(SDL_Event*);

SDL_Window* window = NULL;
SDL_Surface* screen = NULL;

struct {
  int running;
  SDL_Surface* background;
} state;

int SDL_main(int argc, char* argv[])
{
  (void) argc; (void) argv;

  setcwd(argv[0]);

  load_default_settings();

  { // Initialise the window environment
    int error = init_SDL();
    if (error) return error;
  }

  { // Initialise the game state
    int error = init_gamestate();
    if (error) return error;
  }

  while (state.running)
  {
    draw();
    { // Event handling
      SDL_Event e;
      while (SDL_PollEvent(&e))
        event(&e);
    }
    loop();
    SDL_Delay(13);
  }

  close_SDL();
  return 0;
}

int init_SDL(void)
{
  {
    int error = SDL_Init(SDL_INIT_VIDEO);
    if (error < 0) return printerr(
      "SDL Failed to initialise video, error: %s\n",
      SDL_GetError(), error
    );
  }

  window = SDL_CreateWindow(
    "Phthonus",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    settings.window.width,
    settings.window.height,
    SDL_WINDOW_SHOWN
  );

  if (window == NULL)
    return printerr(
      "SDL Window could not be created, error: %s\n",
      SDL_GetError(), -1
    );

  screen = SDL_GetWindowSurface(window);

  return 0;
}

int close_SDL(void)
{

  SDL_FreeSurface(state.background);
  state.background = NULL;

  SDL_DestroyWindow(window);
  window = NULL;

  SDL_Quit();

  return 0;
}

int init_gamestate(void)
{
  state.running = 1;

  {
    int error = loadBMP(&state.background, "assets/background.bmp");
    if (error) return error;
  }

  return 0;
}

// TODO: implement screen drawing
void draw(void)
{
  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0xFF, 0xFF));

  SDL_BlitSurface(state.background, NULL, screen, NULL);

  SDL_UpdateWindowSurface(window);
}

// TODO: main loop
void loop(void)
{

}

// TODO: implement proper event handling
void event(SDL_Event* e)
{
  if (e->type == SDL_QUIT)
  {
    state.running = 0;
    return;
  }
  if (e->type == SDL_KEYDOWN)
  {
    if (e->key.keysym.sym == settings.controls.keyboard.left) {
      move_player(0);
      return;
    }
    if (e->key.keysym.sym == settings.controls.keyboard.right) {
      move_player(1);
      return;
    }
    if (e->key.keysym.sym == settings.controls.keyboard.jump) {
      move_player(2);
      return;
    }
    if (e->key.keysym.sym == settings.controls.keyboard.use) {
      // TODO: bind player use to key
      return;
    }
    return;
  }
  if (e->type == SDL_MOUSEBUTTONDOWN)
  {
    if (e->button.button == settings.controls.mouse.attack) {
      player_spawn_attack();
      return;
    }
    if (e->button.button == settings.controls.mouse.block) {
      player_block();
      return;
    }
  }
}

