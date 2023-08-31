// Copyright (c) Cyuria 2023, see LICENSE.txt for more information

#include "camera.h"

const float CAMERASPEED = 0.2;

camera_s camera;

void update_camera_pos(void)
{
  camera.pos.x += (int) ((camera.pos.x - player.pos.x) * CAMERASPEED);
}

