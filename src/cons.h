#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <raylib.h>
#include "utils/log.h"



#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define SIZE 5.0
#define NUM 50
#define TARGET_LINK (SIZE / ((float) NUM))

#define GRAVITY ((Vector3) {0.0, 0.0f, -3.0})
#define ITERATIONS 8

#define MOUSE_SIZE 10