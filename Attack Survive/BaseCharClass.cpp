#include "BaseCharClass.h"

BaseCharClass::BaseCharClass()
{
}

Vector2 BaseCharClass::getWorldPos() { return worldPos; }

// To undo the movement when hitting the edges
void BaseCharClass::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharClass::GetCollisionRec()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * 3,
        height * 3};
}

void BaseCharClass::tick()
{
    worldPosLastFrame = worldPos;
    // Updating the animation
    runningTime += GetFrameTime();
    if (runningTime >= updateTime)
    {
        runningTime = 0.f;
        frame++;
        if (frame > maxFrame)
            frame = 0;
    }
    // Moving the camera
    // If moving, move the map and animate the running
    if (direction.x != 0.0 || direction.y != 0.0)
    {
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        // Checking if the direction is right or left
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else // Not moving, animate the idle
    {
        texture = idle;
    }
    direction = {};
    // Drawing the character
    //  Which frame sheet to use
    Rectangle source{frame * width, 0.0f, rightLeft * width, height};
    // The Pos and Scale of the knight
    Rectangle dest{getScreenPos().x, getScreenPos().y, 6.f * width, 6.f * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.0, WHITE);
}