#pragma once

#include "../cons.h"
#include <math.h>





Mesh* init_mesh(void);
Material* init_material(void);


void update_mesh(Mesh* mesh, float time);
void draw_mesh(Mesh* mesh, Material* material);
void draw_colored_mesh(Mesh mesh, Vector3 position, Color tint);