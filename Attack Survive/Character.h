#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include <string>
#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "BaseCharClass.h"

class Character : public BaseCharClass
{
    int windWidth{}, windHeight{};
    Texture2D weapon = LoadTexture("characters/weapon_sword.png");
    Rectangle weaponCollisionRec{};
    float health{100.0f};
public:
    Character(int, int);
    // Character Logic
    virtual void tick() override;
    virtual Vector2 getScreenPos() override;
    Rectangle getWeaponCollisionRec() { return weaponCollisionRec; }
    float getHealth() const { return health; }
    void takeDamage(float);
};

#endif