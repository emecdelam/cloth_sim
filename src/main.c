#include "cons.h"
#include "input/key.c"
#include "mesh/cloth.c"
#include "mesh/verlet.c"

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
    



    Cloth* cloth = init_cloth();
    


    log_info("Entering main loop");
    // -- Main game loop
    while (!WindowShouldClose()) {
        HandleKeypress();
        float dt = GetFrameTime();
        if (dt > 0.016f) dt = 0.016f;

        // -- Drawing
        BeginDrawing();
            ClearBackground((Color){ 50, 50, 50, 255 });
            DrawFPS(10, 10);
            // -- Mesh draw
            BeginMode3D(camera);
                draw_cloth(cloth);
            EndMode3D();            
        EndDrawing();
    }
    // -- Cleanup
    log_info("Cleaning up...");

    free_cloth(cloth);
    CloseWindow();    
    return 0;
}