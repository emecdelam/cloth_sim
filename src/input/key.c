#include "../cons.h"


void HandleKeypress(void) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        CloseWindow();
    }
}