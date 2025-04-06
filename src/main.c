#include "cons.h"
#include "mesh/cloth.c"
#include "mesh/verlet.c"
#include <float.h>



void key_press(Cloth* cloth, Camera camera) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        CloseWindow();
    }
    
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        for (int i = 0; i < cloth->n_link; i++) {
            if (cloth->links[i].skip){
                continue;
            }
            Vector2 screen_pos_1 = GetWorldToScreen(cloth->points[cloth->links[i].x1].position, camera);
            Vector2 screen_pos_2 = GetWorldToScreen(cloth->points[cloth->links[i].x2].position, camera);
            if (Vector2Distance(mousePos, screen_pos_1) < MOUSE_SIZE){
                cloth->links[i].skip = true;
            }
            if (Vector2Distance(mousePos, screen_pos_2) < MOUSE_SIZE){
                cloth->links[i].skip = true;
            }
        }
    }   
}

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
        
        // -- Key press
        key_press(cloth, camera);

        // -- Physics
        float dt = GetFrameTime();
        if (dt > 0.016f) dt = 0.016f;
        Vector3 wind = (Vector3){ -0.3f, 0.3f, 0.3f };
        update_cloth(cloth, dt, wind);

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
