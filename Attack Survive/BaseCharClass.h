#ifndef BASE_CHAR_H
#define BASE_CHAR_H
#include <iostream>
#include <string>
#include <vector>
#include "raylib.h"
#include "raymath.h"

class BaseCharClass
{
protected:
    Texture2D texture = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D run = LoadTexture("characters/knight_run_spritesheet.png");
    // Map Pos, Map Position
    // Character view Pos
    Vector2 worldPos{1200, 1120};
    Vector2 worldPosLastFrame{};
    float width{}, height{};
    // Float for flipping the character
    float rightLeft{1.f};
    // Animation variables
    float runningTime{};
    float updateTime{1.f / 12.f};
    int frame{};
    int maxFrame{6};
    float speed{5.f};
    Vector2 direction{};
    bool alive{true};

public:
    BaseCharClass();
    Vector2 getWorldPos();
    // To undo the movement when hitting the edges
    void undoMovement();
    Rectangle GetCollisionRec();
    virtual void tick();
    virtual Vector2 getScreenPos() = 0;
    bool getAlive(){return alive;}
    void setAlive(bool alive){this->alive = alive;}
};

#endif