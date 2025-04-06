#include "mesh.h"
#include "rlgl.h" 



Matrix transform = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

Mesh __mesh;
Material __material;



Mesh* init_mesh(void) {  
    __mesh = GenMeshPlane(7.0,7.0,NUM_X,NUM_Y);
    return &__mesh;
}
Material* init_material(void){
    __material = LoadMaterialDefault();
    __material.maps[MATERIAL_MAP_DIFFUSE].color = RAYWHITE;
    return &__material;
}

void update_mesh(Mesh* mesh, float time) {
    // Safety check
    if (!mesh || mesh->vertices == NULL) return;
    
    // Update each vertex position to create wave effect
    for (int i = 0; i < mesh->vertexCount; i++) {
        float* vert = &mesh->vertices[i*3];
        float x = vert[0];
        float z = vert[2];
        
        // Create wave pattern based on position and time
        float waveHeight = 0.2f;
        float waveFreq = 3.0f;
        float speed = 2.0f;
        
        // Apply sine wave in Y direction (height)
        vert[1] = waveHeight * sinf(waveFreq * (x + z) + time * speed);
    }
    
    // Update the mesh buffer on GPU
    UpdateMeshBuffer(*mesh, 0, mesh->vertices, mesh->vertexCount * 3 * sizeof(float), 0);
}


void draw_mesh(Mesh* mesh, Material* material){
    rlEnableWireMode();
    DrawMesh(*mesh, *material, transform);
    rlDisableWireMode();
}

void draw_colored_mesh(Mesh mesh, Vector3 position, Color tint) {
    Model model = LoadModelFromMesh(mesh);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].color = tint;
    DrawModel(model, position, 1.0f, WHITE);
    UnloadModel(model);
}