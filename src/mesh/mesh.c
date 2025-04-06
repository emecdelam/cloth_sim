#include "mesh.h"
#include "rlgl.h" 
#include "cloth.h"


Matrix transform = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

Mesh __mesh;
Cloth __cloth;

Mesh* init_mesh(void) {
    __mesh = GenMeshPlane(SIZE, SIZE, NUM, NUM);
    return &__mesh;
}


void update_mesh(Mesh* mesh, float time) {
    return;
    if (!mesh || mesh->vertices == NULL) return;
    
    for (int i = 0; i < mesh->vertexCount; i++) {
        float* vert = &mesh->vertices[i*3];
        float x = vert[0];
        float z = vert[2];
        
        float waveHeight = 0.2f;
        float waveFreq = 3.0f;
        float speed = 2.0f;
        
        vert[1] = waveHeight * sinf(waveFreq * (x + z) + time * speed);
    }
    
    UpdateMeshBuffer(*mesh, 0, mesh->vertices, mesh->vertexCount * 3 * sizeof(float), 0);
}


void draw_mesh(Mesh *mesh) {
    Color lineColor = WHITE;
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
                DrawLine3D(v1, v2, lineColor);
            }
            if (z < NUM){
                int idx2 = (z + 1) * vertsPerRow + x;
                Vector3 v2 = {
                    mesh->vertices[idx2 * 3 + 0],
                    mesh->vertices[idx2 * 3 + 1],
                    mesh->vertices[idx2 * 3 + 2]
                };
                DrawLine3D(v1, v2, lineColor);
            }
        }
    }
}