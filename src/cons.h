#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <raylib.h>
#include "utils/log.h"



#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define SIZE 5.0
#define NUM 2
#define TARGET_LINK (SIZE / ((float) NUM))

#define GRAVITY ((Vector3) {0.0, 1.0f, 0.0})
#define ITERATIONS 8