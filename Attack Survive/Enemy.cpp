#include "Enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idleTexture, Texture2D runText)
{
    worldPos = pos;
    texture = idleTexture;
    idle = idleTexture;
    run = runText;
    width = texture.width / maxFrame;
    height = texture.height;
    speed = 4.f;
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}

void Enemy::tick()
{
    if (!getAlive())
        return;
    /* To let the enemy chase the target, we have to put in mind B=C-A
       B is the distenation between enemy and knight
       C is knight pos, A is enemy pos */
    // Subtracting knight pos in screen - enemy pos in screen
    direction = Vector2Subtract(target->getScreenPos(), getScreenPos());
    BaseCharClass::tick();
    if (CheckCollisionRecs(target->GetCollisionRec(), GetCollisionRec()))
        target->takeDamage(damagePerSec * GetFrameTime());
}