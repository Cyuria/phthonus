// Copyright (c) Cyuria 2023, see LICENSE.txt for more information

// define system specific functions
// getcwd(); chdir(); Sleep();
#if defined(_WINDOWS) || defined(_WIN32) || defined(_WIN64)
#define WINDOWS
#include <direct.h>
#define getcwd _getcwd
#define chdir _chdir
#else
#include <unistd.h>
#define Sleep(n) usleep(1000 * (n))
#endif

