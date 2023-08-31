// Copyright (c) Cyuria 2023, see LICENSE.txt for more information

#pragma once
#include "utils.h"
#include "player.h"

typedef struct {
  ivec2 pos;
} camera_s;
extern camera_s camera;

void update_camera_pos(void);

