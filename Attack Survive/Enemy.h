#include <iostream>
#include <string>
#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "BaseCharClass.h"
#include "Character.h"

class Enemy : public BaseCharClass
{
Character* target;
float damagePerSec{10.f};
public:
Enemy(Vector2 pos, Texture2D idleTexture, Texture2D runText);
virtual void tick() override;
void setTarget(Character* knight){target = knight; }
virtual Vector2 getScreenPos() override;
};