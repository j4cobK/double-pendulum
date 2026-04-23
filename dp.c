#include <stdio.h>
#include "raylib.h"
#include <math.h>

#define WIDTH 900
#define HEIGHT 600

#define MASS_RADIUS 20
#define LINE_THICKNESS 4
#define L1 250
#define L2 150
#define G 1000
#define TRACE_LENGTH 100

Vector2 trace[TRACE_LENGTH];

float l1, l2, m1, m2, phi1, phi2, phi1_d, phi2_d, phi1_dd, phi2_dd;

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

    Vector2 end = get_end(start, l1, phi1);
    // Draw bottom pendulum first so theres no overlap
    draw_pendulum(l2, phi2, end);

    draw_pendulum(l1, phi1, start);

    // draw trace of second pendulum
    Vector2 end_l2 = get_end(end, l2, phi2);

    for (int i = TRACE_LENGTH - 1; i > 0; i--)
    {
        trace[i] = trace[i - 1];
    }
    trace[0] = end_l2;

    for (int i = 0; i < TRACE_LENGTH; i++)
    {
        DrawPixelV(trace[i], RED);
    }
}

void step(float dt)
{
    phi1_dd =  -G*(2*m1+m2)*sinf(phi1) - m2*G*sinf(phi1-2*phi2) - 2*sinf(phi1-phi2)*m2*(phi2_d*phi2_d*l2 + phi1_d*phi1_d*l1*cosf(phi1-phi2));
    phi1_dd /= l1*(2*m1+m2-m2*cosf(2*phi1-2*phi2));

    phi2_dd = 2*sinf(phi1-phi2)*(phi1_d*phi1_d*l1*(m1+m2) + G*(m1+m2)*cosf(phi1) + phi2_d*phi2_d*l2*m2*cosf(phi1-phi2));
    phi2_dd /= l2*(2*m1+m2-m2*cosf(2*phi1-2*phi2));

    //angualar velo

    phi1_d += phi1_dd * dt;

    phi2_d += phi2_dd * dt;

    //angle itself
    phi1 += phi1_d * dt;
    phi2 += phi2_d * dt;
}

void init_solver()
{
    phi1 = GetRandomValue(-180, 180) * DEG2RAD;
    phi2 = GetRandomValue(-360, 360) * DEG2RAD;
    phi1_d = 0;
    phi2_d = 0;
    l1 = L1;
    l2 = L2;
    m1 = 2;
    m2 = 2;
}

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "Double Pendulum Simulation");

    SetTargetFPS(120);


    init_solver();
    Vector2 start_pos = (Vector2){WIDTH / 2, 0};
    while (!WindowShouldClose())
    {
        step(GetFrameTime());
        BeginDrawing();
        if (IsKeyPressed(KEY_SPACE))
        {
            init_solver();    
        }
        ClearBackground(BLACK);
        draw_double_pendulum(l1, l2, phi1, phi2, start_pos);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}