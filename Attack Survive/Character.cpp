#include "Character.h"

Character::Character(int windWidth, int windHeight)
    : windWidth{windWidth}, windHeight{windHeight}
{
    width = texture.width / maxFrame;
    height = texture.height;
}

Vector2 Character::getScreenPos()
{
    return Vector2{
        windWidth / 2 - 3 * width,
        windHeight / 2 - 3 * height};
}

void Character::tick()
{
    if (!getAlive())
        return;
    if (IsKeyDown(KEY_W))
        direction.y -= 1;
    if (IsKeyDown(KEY_S))
        direction.y += 1;
    if (IsKeyDown(KEY_A))
        direction.x -= 1;
    if (IsKeyDown(KEY_D))
        direction.x += 1;
    BaseCharClass::tick();
    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    if (rightLeft > 0.f)
    {
        origin = {0.f, weapon.height * 6.f};
        offset = {60.f, 100.5f};
        weaponCollisionRec = {
            getScreenPos().x + (offset.x + 8.f) - weapon.width,
            getScreenPos().y + (offset.y + 6.f) - weapon.height * 6.f,
            weapon.width * 6.f - 10.f,
            weapon.height * 6.f - 10.f};
        rotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? 30.f : 0.f;
    }
    else
    {
        origin = {weapon.width * 6.f, weapon.height * 6.f};
        offset = {50.f, 100.5f};
        weaponCollisionRec = {
            getScreenPos().x + (offset.x + 2.f) - weapon.width * 6.f,
            getScreenPos().y + (offset.y + 2.f) - weapon.height * 6.f,
            weapon.width * 6.f - 14.f,
            weapon.height * 6.f - 14.f};
        rotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? -30.f : 0.f;
    }
    Rectangle source{0.f, 0.f, weapon.width * rightLeft, static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * 5.f, weapon.height * 5.f};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);
    //DrawRectangleLines(weaponCollisionRec.x, weaponCollisionRec.y, weaponCollisionRec.width, weaponCollisionRec.height, RED);
}

void Character::takeDamage(float damage)
{
    health -= damage;
    if (health <= 0)
        setAlive(false);
}
