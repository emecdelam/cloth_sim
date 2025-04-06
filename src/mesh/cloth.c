#include "cloth.h"
#include <math.h>



int find_point(Cloth* cloth, Vector3 pos, float epsilon) {
    for (int i = 0; i < cloth->n_point; i++) {
        Vector3 p = cloth->points[i].position;
        if (fabsf(p.x - pos.x) < epsilon && 
            fabsf(p.y - pos.y) < epsilon && 
            fabsf(p.z - pos.z) < epsilon) {
            return i;
        }
    }
    return -1;
}

int add_point(Cloth* cloth, Vector3 pos) {
    int idx = find_point(cloth, pos, 0.001f);
    if (idx >= 0) {
        return idx;
    }
    
    cloth->points = (ClothPoint*)realloc(cloth->points, sizeof(ClothPoint) * (cloth->n_point + 1));
    
    ClothPoint p = {
        .position = pos,
        .old_position = pos,
        .acceleration = (Vector3){0.0f, 0.0f, 0.0f},
        .constrained = false
    };
    
    if (fabs(pos.z - SIZE/2.0f) < 0.001) {
        p.constrained = true;
    }
    
    cloth->points[cloth->n_point] = p;
    return cloth->n_point++;
}


void add_link(Cloth* cloth, Vector3 x1, Vector3 x2) {
    int idx1 = add_point(cloth, x1);
    int idx2 = add_point(cloth, x2);
    
    if (idx1 == idx2) {
        return;
    }
    
    for (int i = 0; i < cloth->n_link; i++) {
        if ((cloth->links[i].x1 == idx1 && cloth->links[i].x2 == idx2) ||
            (cloth->links[i].x1 == idx2 && cloth->links[i].x2 == idx1)) {
            return;
        }
    }
    
    cloth->links = (ClothLink*)realloc(cloth->links, sizeof(ClothLink) * (cloth->n_link + 1));
    
    ClothLink l = {.x1 = idx1, .x2 = idx2, .skip = false};
    cloth->links[cloth->n_link] = l;
    cloth->n_link++;
}

Cloth* init_cloth(void) {
    Cloth* cloth = (Cloth*)malloc(sizeof(Cloth));
    
    cloth->n_point = 0;
    cloth->n_link = 0;
    cloth->points = NULL;
    cloth->links = NULL;


    for (int z = 0; z <= NUM; z++)
    {
        for (int x = 0; x <= NUM; x++)
        {
            float posX = ((float)x / (float)NUM - 0.5f) * SIZE;
            float posZ = ((float)z / (float)NUM - 0.5f) * SIZE;
            Vector3 v1 = { posX, 0.0f, posZ };
            if (x < NUM)
            {
                float nx = ((float)(x + 1) / (float)NUM - 0.5f) * SIZE;
                Vector3 v2 = { nx, 0.0f, posZ };
                add_link(cloth, v1, v2);
            }
            if (z < NUM)
            {
                float nz = ((float)(z + 1) / (float)NUM - 0.5f) * SIZE;
                Vector3 v2 = { posX, 0.0f, nz };
                add_link(cloth, v1, v2);
            }
        }
    }
    return cloth;
}

void draw_cloth(Cloth* cloth) {
    for (int i = 0; i < cloth->n_link; i++){
        ClothLink link = cloth->links[i];
        if (!link.skip){
            DrawLine3D(cloth->points[link.x1].position, cloth->points[link.x2].position, RAYWHITE);
        }
    }
}

void free_cloth(Cloth* cloth) {
    if (!cloth) return;
    
    if (cloth->points) {
        free(cloth->points);
        cloth->points = NULL;
    }
    
    if (cloth->links) {
        free(cloth->links);
        cloth->links = NULL;
    }
    
    free(cloth);
}