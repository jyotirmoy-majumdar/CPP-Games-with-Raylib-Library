#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGroung(AnimData data, int window_height)
{
    return data.pos.y >= window_height - data.rec.height;
}

void Background(Texture2D back_texture, float &pos1, float speed1, float scale1, float deltatime)
{
    // Drawing the background
    pos1 = pos1 - (speed1 * deltatime);
    if (pos1 <= -(back_texture.width * scale1))
    {
        pos1 = pos1 + (back_texture.width * scale1);
    }
    Vector2 bg_1_pos{pos1, 0.0}; // initialized both the x and y to 0 using braced initialization
    Vector2 bg_2_pos{pos1 + back_texture.width * scale1, 0.0};
    Vector2 bg_3_pos{pos1 + back_texture.width * scale1 * 2.0, 0.0};
    DrawTextureEx(back_texture, bg_1_pos, 0.0, scale1, WHITE);
    DrawTextureEx(back_texture, bg_2_pos, 0.0, scale1, WHITE);
    DrawTextureEx(back_texture, bg_3_pos, 0.0, scale1, WHITE);
}

void Midground(Texture2D mid_texture, float &pos2, float speed2, float scale2, float deltatime)
{
    // Drawing the midground
    pos2 = pos2 - (speed2 * deltatime);
    if (pos2 <= -(mid_texture.width * scale2))
    {
        pos2 = pos2 + (mid_texture.width * scale2);
    }
    Vector2 mg_1_pos{pos2, -80.0};
    Vector2 mg_2_pos{pos2 + mid_texture.width * scale2, -80.0};
    DrawTextureEx(mid_texture, mg_1_pos, 0.0, scale2, WHITE);
    DrawTextureEx(mid_texture, mg_2_pos, 0.0, scale2, WHITE);
}

void Foreground(Texture2D fore_ground, float &pos3, float speed3, float scale3, float deltatime, int window_height)
{
    // Drawing the foreground
    pos3 = pos3 - (90.0) * deltatime;
    if (pos3 <= -(fore_ground.width * 1.5))
    {
        pos3 = pos3 + (fore_ground.width * 1.5);
    }
    Vector2 fg_1_pos{pos3, window_height - fore_ground.height * 1.5};
    Vector2 fg_2_pos{pos3 + fore_ground.width * 1.5, window_height - fore_ground.height * 1.5};
    Vector2 fg_3_pos{pos3 + fore_ground.width * 1.5 * 2.0, window_height - fore_ground.height * 1.5};
    DrawTextureEx(fore_ground, fg_1_pos, 0.0, 1.5, WHITE);
    DrawTextureEx(fore_ground, fg_2_pos, 0.0, 1.5, WHITE);
    DrawTextureEx(fore_ground, fg_3_pos, 0.0, 1.5, WHITE);
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxframe)
{
    // Updating Running Time
    data.runningTime = data.runningTime + deltaTime;
    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;
        // Updating animation frame
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if (data.frame > maxframe)
        {
            data.frame = 0;
        }
    }
    return data;
}

Vector2 PrintingText(Font f, const char *message, float size, float spacing, int width, int height)
{
    // Function to return the middle positions of each texts
    Vector2 TextSize = MeasureTextEx(f, message, size, spacing);
    Vector2 FontPos{
        (width - TextSize.x) / 2.0,
        (height - TextSize.y) / 2.0};

    return FontPos;
}

int main()
{
    const int window_width_x = 800;
    const int window_height_y = 400;

    const char *overtext = "!!! GAME OVER !!!";
    const char *wintext = "!!! YOU WIN !!!";

    InitWindow(window_width_x, window_height_y, "Dapper-Dasher");

    // Acceleration Due to Gravity, (pixels/sec)/sec
    const int gravity = 1000;
    // Initializing velocity
    int velocity;

    // Scarfy jump velocity (pixels per sec)
    const int jump_velocity = -500;
    // Nebula x velocity (pixels per second)
    int nebVel = -300;

    // For the nebula hazard with struct
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // Array of nebulae
    const int noofneb = 15;
    AnimData nebulae[noofneb];
    const int nebulaspacing = 500;

    for (int i = 0; i < noofneb; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width / 8.0;
        nebulae[i].rec.height = nebula.height / 8.0;
        nebulae[i].pos.y = window_height_y - nebulae[i].rec.height;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0 / 16.0;
        nebulae[i].pos.x = window_width_x + i * nebulaspacing;
    }

    // Finish Line
    float finishLine = nebulae[noofneb - 1].pos.x;

    // For the character scarfy with struct
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width / 6.0;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0.0;
    scarfyData.rec.y = 0.0;
    scarfyData.pos.x = window_width_x / 2.0 - scarfyData.rec.width / 2.0;
    scarfyData.pos.y = window_height_y - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.runningTime = 0;

    // Texture for background
    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgx = 0.0;
    // Texture for the midground
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    float mgx = 0.0;
    // Texture for the foreground
    Texture2D foreground = LoadTexture("textures/foreground.png");
    float fgx = 0.0;

    // Collision variable dec for scarfy and nebulae
    bool collision = false;

    // Loading a custom font
    Font gamefont = LoadFont("PixelifySans-VariableFont_wght.ttf");

    SetTargetFPS(60);
    while (WindowShouldClose() != true)
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // Delta Time initialization (time since last frame)
        const float dt = GetFrameTime();

        // Drawing the background
        Background(background, bgx, 30.0, 1.8, dt);
        // Drawing the midground
        Midground(midground, mgx, 60.0, 3.0, dt);
        // Drawing the foreground
        Foreground(foreground, fgx, 90.0, 1.5, dt, window_height_y);

        // Ground Check
        if (isOnGroung(scarfyData, window_height_y))
        {
            // scarfy is on the ground
            velocity = 0;
        }
        else
        {
            // scarfy is in the air
            velocity = velocity + gravity * dt; // Updating the gravity with dt
        }

        if (IsKeyPressed(KEY_SPACE) && isOnGroung(scarfyData, window_height_y))
        {
            // Jumping only once, no duble jumping
            // Substracting the velocity to negative from the zero to initiate jump
            velocity = velocity + jump_velocity;
        }
        for (int i = 0; i < noofneb; i++)
        {
            // Updating the position of each nebula
            nebulae[i].pos.x = nebulae[i].pos.x + nebVel * dt;
        }

        // Updating the finish line
        finishLine = finishLine + nebVel * dt;
        // Updating the Position of scarfy
        scarfyData.pos.y = scarfyData.pos.y + velocity * dt; // updating the position with dt

        for (int i = 0; i < noofneb; i++)
        {
            // Running Time updation for nebulae
            nebulae[i].runningTime = nebulae[i].runningTime + dt;
        }

        if (isOnGroung(scarfyData, window_height_y))
        {
            // Updating Scarfy's Animation frame by calling the function
            scarfyData = updateAnimData(scarfyData, dt, 5);
        }

        for (int i = 0; i < noofneb; i++)
        {
            // Updating Nebula's Animation Frame by calling the function
            nebulae[i] = updateAnimData(nebulae[i], dt, 61);
        }

        // Collision detection
        for (AnimData nebula : nebulae) // range based loop to iterate through every elements
        {
            float pad = 50.0; // padding to reduce the collision box for nebula
            Rectangle nebRec{
                nebula.pos.x + pad,
                nebula.pos.y + pad,
                nebula.rec.width - 2.0 * pad,
                nebula.rec.height - 2.0 * pad};
            Rectangle scarfyrec{
                scarfyData.pos.x,
                scarfyData.pos.y,
                scarfyData.rec.width,
                scarfyData.rec.height};
            if (CheckCollisionRecs(nebRec, scarfyrec))
            {
                // Collision of scarfy and nebula happened
                collision = true;
            }
        }

        // Vector that stores the mid of each text after taking the return from the function called
        Vector2 FontPos_1 = PrintingText(gamefont, wintext, 50.0, 0.0, window_width_x, window_height_y);
        Vector2 FontPos_2 = PrintingText(gamefont, overtext, 50.0, 0.0, window_width_x, window_height_y);

        if (collision == false)
        {
            // Game still running
            for (int i = 0; i < noofneb; i++)
            {
                // Drawing Nebula
                DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
            }

            if (scarfyData.pos.x > finishLine + 20.0)
            {
                // You Win
                DrawTextEx(gamefont, wintext, FontPos_1, 50.0, 0.0, WHITE);
            }
            else
            {
                // Drawing Scarfy
                DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
            }
        }
        else
        {
            // Game Over
            DrawTextEx(gamefont, overtext, FontPos_2, 50.0, 0.0, WHITE);
        }
        EndDrawing();
    }
    // Unloading Textures
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);

    CloseWindow();
}