#include "verlet.h"
#include "raylib.h"
#include "raymath.h"



void verlet_point(ClothPoint* point, float dt) {
    if (point->constrained) {
        return;
    }
    Vector3 velocity = Vector3Subtract(point->position, point->old_position);
    point->old_position = point->position;
    point->position = Vector3Add(Vector3Add(point->position, velocity), Vector3Scale(point->acceleration, dt * dt));
}

void verlet_point_solver(Cloth* cloth, float dt, Vector3 wind) {
    for (int i = 0; i < cloth->n_point; i++) {
        cloth->points[i].acceleration = Vector3Add(GRAVITY, wind);
        verlet_point(&cloth->points[i], dt);
    }
}

void verlet_link(Cloth* cloth, ClothLink* link) {
    ClothPoint* x1 = &cloth->points[link->x1];
    ClothPoint* x2 = &cloth->points[link->x2];
    
    Vector3 axis = Vector3Subtract(x1->position, x2->position);
    float length = Vector3Length(axis);
    if (length < 0.0001f) return;
    
    Vector3 n = Vector3Scale(axis, 1.0f/length);
    float delta = TARGET_LINK - length;
    
    if (x1->constrained && x2->constrained) {
        return;
    } 
    else if (x1->constrained) {
        x2->position = Vector3Subtract(x2->position, Vector3Scale(n, delta));
    }
    else if (x2->constrained) {
        x1->position = Vector3Add(x1->position, Vector3Scale(n, delta));
    }
    else {
        x1->position = Vector3Add(x1->position, Vector3Scale(n, delta * 0.5f));
        x2->position = Vector3Subtract(x2->position, Vector3Scale(n, delta * 0.5f));
    }
}


void apply_acceleration(Cloth* cloth, Vector3 acc) {
    for (int i = 0; i < cloth->n_point; i++) {
        cloth->points[i].acceleration = Vector3Add(cloth->points[i].acceleration, acc);
    }
}


void update_cloth(Cloth* cloth, float dt, Vector3 wind) {
    verlet_point_solver(cloth, dt, wind);
    for (int iter = 0; iter < ITERATIONS; iter++) {
        for (int i = 0; i < cloth->n_link; i++) {
            if (!cloth->links[i].skip){
                verlet_link(cloth, &cloth->links[i]);
            }
        }
    }
}