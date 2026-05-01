#pragma once
#include "Entity.h"
#include "Enemy.h"
 #include"Globals.h"


class Tower : public Entity
{
protected:
    int   damage;  
    float range;   
    Enemy* target;  

public:
    Tower(float x, float y, int damage, float range)
        : Entity(x, y, 999), damage(damage), range(range), target(nullptr) {
    }

    virtual void attack() = 0;  

    void update() override {}   

    void setTarget(Enemy* e) { target = e; }

    bool inRange(Enemy* e) const
    {
        float dx = e->getX() - x;
        float dy = e->getY() - y;
        return (dx * dx + dy * dy) <= (range * range);
    }

    virtual ~Tower() {}
};
