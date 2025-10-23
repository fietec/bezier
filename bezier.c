#include <stdio.h>
#include <stdbool.h>

#define NOB_STRIP_PREFIX
#include "raylib.h"
#include "raymath.h"

#define NOB_IMPLEMENTATION
#include "nob.h"

typedef struct{
    Vector2 *items;
    size_t count;
    size_t capacity;
} Points;

static Points points = {0};
static Points plots = {0};

int main(void)
{
    InitWindow(800, 600, "Bezier");

    while (!WindowShouldClose()){
        BeginDrawing();
        
        ClearBackground(GetColor(0x181818FF));

        Vector2 point_size = {20, 20};
        Vector2 plot_size = {10, 10};

        if (IsKeyPressed(KEY_BACKSPACE)){
            points.count = 0;
            plots.count = 0;
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            Vector2 mouse = GetMousePosition();
            da_append(&points, mouse);
        }
        
        for (int i=0; i<(int)points.count-2; i+=2){
            Vector2 p1 = points.items[i];
            Vector2 p2 = points.items[i+1];
            Vector2 p3 = points.items[i+2];

            size_t n = 40;
            for (size_t j=0; j<=n; ++j){
                float t = (float) j/n;
                Vector2 plot = Vector2Lerp(Vector2Lerp(p1, p2, t), Vector2Lerp(p2, p3, t), t);
                da_append(&plots, plot);
            }
        }
        for (size_t i=0; i<points.count; ++i){
            Vector2 position = Vector2Subtract(points.items[i], Vector2Scale(point_size, 0.5f));
            DrawRectangleV(position, point_size, RED);
        }
        for (size_t i=0; i<plots.count; ++i){
            Vector2 position = Vector2Subtract(plots.items[i], Vector2Scale(plot_size, 0.5f));
            DrawRectangleV(position, plot_size, BLUE);
        }
        plots.count = 0;
        
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
