#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <raylib.h>
#include "utils/log.h"


// -- Viewport
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define SIZE 5.0 // Size fo the cloth
#define NUM 50 // Number of square
#define TARGET_LINK (SIZE / ((float) NUM)) // Watch out for rounding

#define GRAVITY ((Vector3) {0.0, 0.0f, -2.5})
#define ITERATIONS 8 // Verlet interations

#define MOUSE_SIZE 10 // Radius to delete cloth