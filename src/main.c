#include "cons.h"
#include "mesh/mesh.c"
#include "input/key.c"
#include "mesh/cloth.c"


int main() {
    log_info("Starting program");
    
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Cloth Sim");
    log_info("Window created");
    
    SetTargetFPS(60);
    log_info("Raylib Version: %s", RAYLIB_VERSION);
    

    
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 7.0f, 0.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 0.0f, 1.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    


    Mesh* mesh = init_mesh();

    

    float start_time = 0.0f;
    log_info("Entering main loop");
    // -- Main game loop
    while (!WindowShouldClose()) {
        HandleKeypress();
        start_time += GetFrameTime();
        update_mesh(&__mesh, start_time);
        // -- Drawing
        BeginDrawing();
            ClearBackground((Color){ 50, 50, 50, 255 });
            DrawFPS(10, 10);
            // -- Mesh draw
            BeginMode3D(camera);
                draw_mesh(mesh);
            EndMode3D();            
        EndDrawing();
    }
    // -- Cleanup
    log_info("Cleaning up...");
    UnloadMesh(*mesh);
    CloseWindow();    
    return 0;
}