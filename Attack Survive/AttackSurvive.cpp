#include <iostream>
#include <string>
#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Enemy.h"

int main()
{
    int windWidth{800}, windHeight{800};
    InitWindow(windWidth, windHeight, "Attack Survive");
    // Loading the map
    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos{};
    float mapScale{4.f};
    // Setting the frames
    SetTargetFPS(60);
    Character Knight(windWidth, windHeight);
    Enemy Goblin1{
        Vector2{800.f,300.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};
    Enemy Goblin2{
        Vector2{100.f,900.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};
    Enemy Goblin3{
        Vector2{800.f,900.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};
    Enemy Goblin4{
        Vector2{1300.f,300.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};
    Enemy* goblins[]{&Goblin1,&Goblin2,&Goblin3,&Goblin4};
    for(auto enemies:goblins)
    enemies->setTarget(&Knight);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        // Adjusting the map when moving
        mapPos = Vector2Scale(Knight.getWorldPos(), -1.f);
        // Drawing the map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);
        if (!Knight.getAlive())
        {
            DrawText("You Died!", 240, 400, 70, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string health{"Health: "};
            health.append(std::to_string(Knight.getHealth()), 0, 5);
            DrawText(health.c_str(), 0, 0, 50, GREEN);
        }
        // Character Logic
        Knight.tick();
        for(auto enemies:goblins)
        enemies->tick();
        //  If knight reches the edge, stop moving
        if (Knight.getWorldPos().x < 120.f ||
            Knight.getWorldPos().y < 120.f ||
            Knight.getWorldPos().x + windWidth > (map.width - 30) * mapScale ||
            Knight.getWorldPos().y + windHeight > (map.height - 35) * mapScale)
            Knight.undoMovement();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            for(auto enemies:goblins)
                if (CheckCollisionRecs(Knight.getWeaponCollisionRec(), enemies->GetCollisionRec()))
                    enemies->setAlive(false);
        EndDrawing();
    }
    CloseWindow();
}