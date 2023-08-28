// Copyright (c) Cyuria 2023, see LICENSE.txt for more information

#include "settings.h"
#include <stdio.h>

#include "utils.h"

settings_s settings;
const char* settingsfilename = "settings.bin";
const size_t settingssize = 5 * sizeof(int) + 4 * sizeof(SDL_Keycode) + 2 * sizeof(int);

void load_settings(void)
{
  FILE* settingsfile = NULL;
  int error = fopen_s(&settingsfile, settingsfilename, "rb");

  if (error || settingsfile == NULL) {
    fprintf(stderr, "Could not open settings file, error code: %d\n", error);
    return;
  }

  // Check for an invalid file
  fseek(settingsfile, 0L, SEEK_END);
  size_t fsize = ftell(settingsfile);
  rewind(settingsfile);
  if (fsize != settingssize)
  {
    fprintf(stderr, "Error, invalid settings file (%s)\n", settingsfilename);
    return;
  }

  // Load settings

  { // window
    int buffer[5];
    fread(buffer, sizeof(int), sizeof(buffer) / sizeof(int), settingsfile);
    settings.window.width = buffer[0];
    settings.window.height = buffer[1];
    settings.window.refresh = buffer[2];
    settings.window.vsync = buffer[3];
    settings.window.flags = buffer[4];
  }
  { // keyboard controls
    SDL_Keycode buffer[4];
    fread(buffer, sizeof(SDL_Keycode), sizeof(buffer) / sizeof(SDL_Keycode), settingsfile);
    settings.controls.keyboard.left = buffer[0];
    settings.controls.keyboard.right = buffer[0];
    settings.controls.keyboard.jump = buffer[0];
    settings.controls.keyboard.use = buffer[0];
  }
  { // mouse controls
    int buffer[2];
    fread(buffer, sizeof(int), sizeof(buffer) / sizeof(int), settingsfile);
    settings.controls.mouse.attack = buffer[0];
    settings.controls.mouse.block = buffer[1];
  }

  /*
  {
    int buffer[];
    fread(buffer, sizeof(int), sizeof(buffer) / sizeof(int), settingsfile);
    settings = buffer[];
  }
  */

  fclose(settingsfile);
}

void save_settings(void)
{
  FILE* settingsfile = NULL;
  int error = fopen_s(&settingsfile, settingsfilename, "wb");

  if (settingsfile == NULL) {
    fprintf(stderr, "Could not open settings file, error code: %d\n", error);
    exit(error);
  }

  { // window
    int buffer[] = {
      settings.window.width,
      settings.window.height,
      settings.window.refresh,
      settings.window.vsync,
      settings.window.flags
    };
    fwrite(buffer, sizeof(int), sizeof(buffer) / sizeof(int), settingsfile);
  }
  { // keyboard controls
    SDL_Keycode buffer[] = {
      settings.controls.keyboard.left,
      settings.controls.keyboard.right,
      settings.controls.keyboard.jump,
      settings.controls.keyboard.use
    };
    fwrite(buffer, sizeof(SDL_Keycode), sizeof(buffer) / sizeof(SDL_Keycode), settingsfile);
  }
  { // mouse controls
    int buffer[] = {
      settings.controls.mouse.attack,
      settings.controls.mouse.block
    };
    fwrite(buffer, sizeof(int), sizeof(buffer) / sizeof(int), settingsfile);
  }

  fclose(settingsfile);
}

void load_default_settings(void)
{
  settings.window.width = 1280;
  settings.window.height = 720;
  settings.window.refresh = 60;
  settings.window.vsync = 1;
  settings.window.flags = 0;

  settings.controls.keyboard.left = SDLK_a;
  settings.controls.keyboard.right = SDLK_d;
  settings.controls.keyboard.jump = SDLK_w;
  settings.controls.keyboard.use = SDLK_SPACE;
  settings.controls.mouse.attack = SDL_BUTTON_LEFT;
  settings.controls.mouse.block = SDL_BUTTON_RIGHT;

}

