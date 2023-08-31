// Copyright (c) Cyuria 2023, see LICENSE.txt for more information

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sdl/SDL.h>

#include "assets.h"
#include "camera.h"
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
SDL_Renderer* renderer = NULL;

struct {
  int running;
  SDL_Texture* background;
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

  renderer = SDL_CreateRenderer(
    window, -1,
    SDL_RENDERER_ACCELERATED
  );

  if (renderer == NULL)
    return printerr(
      "SDL Renderer could not be created, error: %s\n",
      SDL_GetError(), -1
    );

  return 0;
}

int close_SDL(void)
{

  SDL_DestroyTexture(state.background);
  state.background = NULL;

  SDL_DestroyRenderer(renderer);
  renderer = NULL;

  SDL_DestroyWindow(window);
  window = NULL;

  SDL_Quit();

  return 0;
}

int init_gamestate(void)
{
  state.running = 1;

  {
    int error = loadBMP(renderer, &state.background, "assets/background.bmp");
    if (error) return error;
  }

  {
    int error = loadAllTextures(renderer);
    if (error) return error;
  }

  return 0;
}

// TODO: implement screen drawing
void draw(void)
{
  SDL_RenderClear(renderer);

  SDL_RenderCopy(renderer, state.background, NULL, NULL);

  SDL_RenderPresent(renderer);
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
      ivec2 mousepos;
      SDL_GetMouseState(&mousepos.x, &mousepos.y);
      mousepos.x -= camera.pos.x;
      mousepos.y -= camera.pos.y;
      const float invlength = 1 / ivec2_len(mousepos);
      const fvec2 mouserelpos = {
        .x = mousepos.x * invlength,
        .y = mousepos.y * invlength
      };
      player_attack(mouserelpos);
      return;
    }
    if (e->button.button == settings.controls.mouse.block) {
      if (player.blocking) return;
      player_start_block();
      return;
    }
    return;
  }
  if (e->type == SDL_MOUSEBUTTONUP)
  {
    if (e->button.button == settings.controls.mouse.block) {
      if (!player.blocking) return;
      player_stop_block();
      return;
    }
    return;
  }
}

