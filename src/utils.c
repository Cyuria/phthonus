// Copyright (c) Cyuria 2023, see LICENSE.txt for more information

#include "utils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "system.h"

int printerr(const char* err, const char* errmsg, const int retval)
{
  fprintf(stderr, err, errmsg);
  return retval;
}

void setcwd(char* exepath)
{
  // find index of last slash in argv
  size_t parent = 0;
  for (size_t i = 0; exepath[i]; ++i)
    if (exepath[i] == '/' || exepath[i] == '\\') parent = i;

  // Change the current working directory
  char* path = malloc(parent + 1);
  memcpy(path, exepath, parent);
  path[parent] = 0;
  chdir(path);
  free(path);
}

float ivec2_len(const ivec2 v)
{
  return sqrtf(v.x * v.x + v.y * v.y);
}
float fvec2_len(const fvec2 v)
{
  return sqrtf(v.x * v.x + v.y * v.y);
}

