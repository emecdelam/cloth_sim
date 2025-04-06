#pragma once
#include "../cons.h"


typedef struct Point {
    Vector3 position;
    Vector3 acceleration;
    Vector3 old_position;
} ClothPoint;

typedef struct Link {
    ClothPoint* x1;
    ClothPoint* x2;
} ClothLink;

typedef struct Cloth {
    unsigned int n_point;
    ClothPoint* points;
    unsigned int n_link;
    ClothLink* links;
} Cloth;

void verlet_point(ClothPoint* point, float dt);
void verlet_point_solver(Cloth* cloth ,float dt);
void verlet_link(ClothLink* link);
void apply_acceleration(Cloth* cloth, Vector3 acc);
Cloth* init_cloth(Mesh* mesh);