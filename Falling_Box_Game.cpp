#include "raylib.h"

int main()
{
    int width_x = 600;
    int height_y = 900;

    InitWindow(width_x, height_y, "Falling Box Game");

    // Circle Coordinates
    int circle_x = width_x / 2;
    int circle_y = 800;
    int radius = 25;
    int distance = 10;

    // Circle Bounding Box
    int circle_top, circle_bottom;
    int circle_left, circle_right;

    // Box Coordinates
    int box_x = width_x / 2;
    int box_y = 0;
    int side = 40;

    // Bounding Box of the Box
    int box_left, box_right;
    int box_top, box_bottom;

    // Game Over flag
    bool gameover = false;

    SetTargetFPS(60);
    while (WindowShouldClose() != true)
    {
        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        if (gameover == false)
        {
            // Drawing the Circle
            DrawCircle(circle_x, circle_y, radius, BLUE);
            if (IsKeyDown(KEY_RIGHT))
            {
                // Cicle moving right along with right boundary condition
                circle_x = circle_x + distance;
                if (circle_x + radius > width_x)
                {
                    circle_x = circle_x - distance;
                }
            }
            if (IsKeyDown(KEY_LEFT))
            {
                // Circle moving left along with left boundary condition
                circle_x = circle_x - distance;
                if (circle_x - radius < 0)
                {
                    circle_x = circle_x + distance;
                }
            }

            // Updating the bounding box of the circle
            circle_top = circle_y - radius;
            circle_bottom = circle_y + radius;
            circle_left = circle_x - radius;
            circle_right = circle_x + radius;

            // Drawing the box
            DrawRectangle(box_x, box_y, side, side, RED);
            // Box moving down
            box_y = box_y + 10;
            if (box_y == height_y)
            {
                // Box respaning to the top with random x position
                box_y = 0;
                box_x = GetRandomValue(side, width_x - side);
            }

            // Updating the Bounding box of the box
            box_left = box_x;
            box_bottom = box_y + side;
            box_top = box_y;
            box_right = box_x + side;

            // Collision checking
            bool collision_detection = false;
            collision_detection = ((box_top <= circle_bottom) &&
                                   (box_bottom >= circle_top) &&
                                   (box_left <= circle_right) &&
                                   (box_right >= circle_left));

            if (collision_detection == true)
            {
                gameover = true;
            }
        }
        else
        {
            DrawText("!!!GAME OVER!!!", width_x / 4, height_y / 2, 40, DARKBROWN);
        }
        EndDrawing();
    }
}