#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>
#include <time.h>

#define bodyLength 50
#define SCREEN_HEIGHT 1000
#define SCREEN_WIDTH 1000

typedef struct Circle {
    Vector2 pos;
    Vector2 v;
    float radius;
    Color color;
} Circle;



void DrawCircleSt(Circle c) {
    DrawCircleLinesV(c.pos, c.radius, c.color);
}



void MoveDot(Circle* c) {
    c->pos.x += c->v.x;
    c->pos.y += c->v.y;
}

// Vector2 calculateDistanceVector(Vector2 v1, Vector2 v2) { 
//     return (Vector2) {v2.x - v1.x, v2.y - v1.y};
// }

Vector2 ApplyDistanceConstraint(Vector2 anchor, Vector2 point, float distance) {
    // Calculate the vector from anchor to point
    Vector2 direction = Vector2Subtract(point, anchor);

    // Get the length of this vector
    float currentDistance = Vector2Length(direction);

    // Normalize the vector (to make it unit length)
    Vector2 unitDirection = Vector2Scale(direction, 1.0f / currentDistance);

    // Scale it to the desired distance
    Vector2 constrainedVector = Vector2Scale(unitDirection, distance);

    // Calculate the new position for the point
    Vector2 newPosition = Vector2Add(anchor, constrainedVector);

    return newPosition;
}


int main(int argc, char const *argv[])
{
    srand(time(NULL));
    Color DOT = (Color){210, 212, 212, 255};
    Color BG = (Color){39, 45, 53, 255};

    Circle c[bodyLength] = {0};

    for (int i = 0; i < bodyLength; i++)
    {
        c[i].pos.x = (rand() % SCREEN_WIDTH) + 1;
        c[i].pos.y = (rand() % SCREEN_HEIGHT) + 1;
        // c[i].radius = (rand() % 10) + 1;
        if (i <= 2) {
            c[i].radius = 50.0f - (10*i);        
        // } else if (i >= bodyLength - 3) {
        //     c[i].radius = 10.0f - (5*(1/i));
        } else {
            c[i].radius = 20.0f;
        }
        c[i].color = DOT;
    }
    
    InitWindow(SCREEN_HEIGHT, SCREEN_WIDTH, "Procedural Snake");
    SetTargetFPS(120);

    // Circle c1 = {(Vector2){100,100}, (Vector2){10,10}, 50, WHITE};
    // Circle c2 = {(Vector2){c1.pos.x+c1.radius, c1.pos.y+c1.radius}, (Vector2){0,0}, c1.radius, WHITE};

    while(!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);
            // printf("%f %f \n", c2.pos.x, c2.pos.y);
            c[0].pos = GetMousePosition();
            for (int i = 0; i < bodyLength - 1; i++) {
                c[i+1].pos = ApplyDistanceConstraint(c[i].pos, c[i+1].pos, c[i].radius);
                DrawCircleSt(c[i]);
            }
        EndDrawing();
    }
    return 0;
}