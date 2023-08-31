// Copyright (c) Cyuria 2023, see LICENSE.txt for more information

#pragma once

int printerr(const char*, const char*, const int);

void setcwd(char*);

typedef struct {
  float x;
  float y;
} fvec2;
typedef struct {
  int x;
  int y;
} ivec2;

float ivec2_len(ivec2 v);
float fvec2_len(fvec2 v);

