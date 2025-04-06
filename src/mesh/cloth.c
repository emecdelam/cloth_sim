#include "cloth.h"
#include "raymath.h"



void verlet_point(ClothPoint* point, float dt){
    Vector3 velocity = Vector3Subtract(point->position, point->old_position);
    point->old_position = point->position;
    point->position = Vector3Add(Vector3Add(point->position,velocity), Vector3Scale(point->acceleration, dt * dt));
}

void verlet_point_solver(Cloth* cloth ,float dt){
    for (unsigned int i = 0; i< cloth->n_point; i++){
        ClothPoint point = cloth->points[i];
        point.acceleration = Vector3Add(point.acceleration, GRAVITY);
        verlet_point(&point, dt);
    }
}

void verlet_link(ClothLink* link){
    Vector3 axis = Vector3Subtract(link->x1->position, link->x2->position);
    float length = Vector3Length(axis);
    Vector3 n = Vector3Scale(axis, 1/length);
    float delta =  TARGET_LINK- length;
    link->x1->position = Vector3Add(link->x1->position, Vector3Scale(n, delta * 0.5f));
    link->x2->position = Vector3Subtract(link->x2->position, Vector3Scale(n, delta * 0.5f));
}

void apply_acceleration(Cloth* cloth, Vector3 acc){
    for (unsigned int i = 0; i< cloth->n_point; i++){
        ClothPoint point = cloth->points[i];
        point.acceleration = Vector3Add(point.acceleration, acc);
    }
}
void add_link(Cloth* cloth, Vector3 x1, Vector3 x2){
    ClothPoint p1 = (ClothPoint) {x1, (Vector3){0.0, 0.0, 0.0}, x1};
    ClothPoint p2 = (ClothPoint) {x2, (Vector3){0.0, 0.0, 0.0}, x2};
    ClothLink l = (ClothLink) {&p1, &p2};
    cloth->links[cloth->n_link] = l;
    cloth->n_link++;
    cloth->points[cloth->n_point] = p1;
    cloth->n_point++;
    cloth->points[cloth->n_point] = p2;
    cloth->n_point++;
}

Cloth* init_cloth(Mesh* mesh) {
    Cloth* cloth = (Cloth*) malloc(sizeof(Cloth));
    cloth->links = malloc(sizeof(ClothLink)*(2*NUM)*(NUM+1));
    cloth->points = malloc(sizeof(ClothPoint) * (NUM+1) * (NUM+1));


    int vertsPerRow = NUM + 1;
    for (int z = 0; z <= NUM; z++)
    {
        for (int x = 0; x <= NUM; x++)
        {
            int idx1 = z * vertsPerRow + x;
            Vector3 v1 = {
                mesh->vertices[idx1 * 3 + 0],
                mesh->vertices[idx1 * 3 + 1],
                mesh->vertices[idx1 * 3 + 2]
            };
            if (x < NUM){
                int idx2 = idx1 + 1;
                Vector3 v2 = {
                    mesh->vertices[idx2 * 3 + 0],
                    mesh->vertices[idx2 * 3 + 1],
                    mesh->vertices[idx2 * 3 + 2]
                };
                add_link(cloth, v1, v2);
            }
            if (z < NUM){
                int idx2 = (z + 1) * vertsPerRow + x;
                Vector3 v2 = {
                    mesh->vertices[idx2 * 3 + 0],
                    mesh->vertices[idx2 * 3 + 1],
                    mesh->vertices[idx2 * 3 + 2]
                };
                add_link(cloth, v1, v2);
            }
        }
    }
    return cloth;
}
void free_cloth(Cloth* cloth){
    if (cloth->points != NULL)
    {
        free(cloth->points);
        cloth->points = NULL;
    }

    if (cloth->links != NULL)
    {
        free(cloth->links);
        cloth->links = NULL;
    }
    cloth->n_point = 0;
    cloth->n_link = 0;
}