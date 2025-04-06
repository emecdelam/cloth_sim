#pragma once


#include "raymath.h"
#include "../cons.h"
#include "cloth.h"


void verlet_point(ClothPoint* point, float dt);
void verlet_link(Cloth* cloth, ClothLink* link);
void apply_acceleration(Cloth* cloth, Vector3 acc);
void update_cloth(Cloth* cloth, float dt, Vector3 wind);