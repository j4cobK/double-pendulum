#include <stdio.h>
#include "raylib.h"
#include <math.h>

#define WIDTH 900
#define HEIGHT 600

#define MASS_RADIUS 20
#define LINE_THICKNESS 4
#define L1 250
#define L2 250

Vector2 start_pos = (Vector2){WIDTH / 2, 0};


Vector2 get_end(Vector2 start, float l, float phi)
{
    return (Vector2){start.x + l * sinf(phi), start.y + l * cosf(phi)};
}

void draw_pendulum(float l, float phi, Vector2 start)
{
    Vector2 end = get_end(start, l, phi);
    DrawLineEx(start, end, LINE_THICKNESS, WHITE);
    DrawCircleV(end, MASS_RADIUS, RED);
}

void draw_double_pendulum(float l1, float l2, float phi1, float phi2, Vector2 start)
{
    draw_pendulum(l1, phi1, start);

    Vector2 end = get_end(start, l1, phi1);
    draw_pendulum(l2, phi2, end);
}

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "Double Pendulum Simulation");

    SetTargetFPS(60);

    Vector2 start_pos = (Vector2){WIDTH / 2, 0};
    while (!WindowShouldClose())
    {
        BeginDrawing();

        draw_double_pendulum(L1, L2, DEG2RAD * 50, DEG2RAD * -30, start_pos);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}