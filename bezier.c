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

static int dragging = -1;

int main(void)
{
    InitWindow(800, 600, "Bezier");

    while (!WindowShouldClose()){
        BeginDrawing();
        
        ClearBackground(GetColor(0x181818FF));

        Vector2 point_size = {20, 20};
        Vector2 plot_size = {10, 10};
        Vector2 mouse = GetMousePosition();

        if (IsKeyPressed(KEY_ENTER)){
            points.count = 0;
            plots.count = 0;
        }
        if (IsKeyPressed(KEY_BACKSPACE) && points.count > 0){
            --points.count;
        }
        
        for (int i=0; i<(int)points.count-2; i+=2){
            Vector2 p1 = points.items[i];
            Vector2 p2 = points.items[i+1];
            Vector2 p3 = points.items[i+2];

            size_t n = 40;
            for (size_t j=0; j<=n; ++j){
                float t = (float)j/n;
                Vector2 plot = Vector2Lerp(Vector2Lerp(p1, p2, t), Vector2Lerp(p2, p3, t), t);
                da_append(&plots, plot);
            }
        }
        for (size_t i=0; i<points.count; ++i){
            Vector2 position = Vector2Subtract(points.items[i], Vector2Scale(point_size, 0.5f));

            bool hover = CheckCollisionPointRec(mouse, (Rectangle) {position.x, position.y, point_size.x, point_size.y});
            if (hover){
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) dragging = i;
                else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) dragging = -1;
            }
                
            DrawRectangleV(position, point_size, RED);
        }
        if (dragging >= 0){
            points.items[dragging] = mouse;
        } else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            da_append(&points, mouse);
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
