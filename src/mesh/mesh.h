#pragma once

#include "../cons.h"
#include <math.h>





Mesh* init_mesh(void);


void update_mesh(Mesh* mesh, float time);
void draw_mesh(Mesh* mesh);
