// Copyright (c) Cyuria 2023, see LICENSE.txt for more information

#pragma once
#include <sdl/SDL.h>

typedef struct {
  struct {
    int width;
    int height;
    int refresh;
    int vsync;
    int flags;
  } window;
  struct {
    struct {
      SDL_Keycode left;
      SDL_Keycode right;
      SDL_Keycode jump;
      SDL_Keycode use;
    } keyboard;
    struct {
      int attack;
      int block;
    } mouse;
  } controls;
} settings_s;
extern settings_s settings;

void load_default_settings(void);

void load_settings(void);

void save_settings(void);

