#include "../cons.h"


void HandleKeypress(void) {
    // Check for specific keys
    if (IsKeyPressed(KEY_ESCAPE)) {
        // Close the window
        CloseWindow();
    }
    
    // Add other key handling from your key_callback function
}