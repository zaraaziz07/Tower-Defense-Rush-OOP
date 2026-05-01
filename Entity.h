#pragma once
#include"Globals.h"
class Entity {
protected:
    float x;
    float y;
    int hp;
    int maxHp;
public:
    Entity(float x, float y, int hp) : x(x), y(y), hp(hp), maxHp(hp) {}

    virtual void update() = 0;  //movement logic
    virtual void render(sf::RenderWindow& window) = 0;
    virtual string getType()const=0;
    virtual void takeDamage(int dmg)
    {
        dmg = -hp;
        if (hp < 0)
            hp = 0;

    }
    bool  isAlive() const { return hp > 0; }
    float getX()    const { return x; }
    float getY()    const { return y; }

    virtual ~Entity() {}
};

