#pragma once
#include <SFML/Graphics.hpp>
#include"Entity.h"
#include"Globals.h"
class Enemy:public Entity {
protected:
	float speed;
	int reward;
	int pathIndex;
public:
    Enemy(float x, float y, int hp, float speed, int reward)
        : Entity(x, y, hp), speed(speed), reward(reward), pathIndex(0) {
    }

    virtual void move() = 0;

    void update() override { move(); } 

    int   getReward()    const { return reward; }
    float getSpeed()     const { return speed; }
    void  setSpeed(float s) { speed = s; }  

    virtual ~Enemy() {}
};
class BasicEnemy:public Enemy {
    sf::Texture texture;
    sf::Sprite sprite;
    WayPoint* path;   //A pointer that points to the WayPoints array
    int pathCount;    //Shows how many WayPoints
public:
    BasicEnemy(WayPoint* path,int pathCount) :Enemy(path[0].x, path[0].y, 100, 2.0f, 10)
    ,path(path), pathCount(pathCount)
    {
        if (!texture.loadFromFile("assets/BasicEnemy.png"))
        {

        }
        sprite.setTexture(texture);
        float sx = 32.f / texture.getSize().x;
        float sy = 32.f / texture.getSize().y;
        sprite.setScale(sx, sy);
    }
    void move()override
    {
        if (pathIndex >= pathCount) return;
        float targetX = path[pathIndex].x;
        float targetY = path[pathIndex].y;
        float dx = targetX - x;
        float dy = targetY - y;
        float dist = sqrt(dx * dx + dy * dy);

        if (dist <= speed)
        {
            x = targetX;
            y = targetY;
            pathIndex++;
        }
        else
        {
            if (dist == 0.f) return;
            x += (dx / dist) * speed;
            y += (dy / dist) * speed;
        }
    }

    void render(sf::RenderWindow& window) override
    {
        sprite.setPosition(x, y);
        window.draw(sprite);
        
        sf::RectangleShape bgBar(sf::Vector2f(32, 5));
        bgBar.setFillColor(sf::Color::Red);
        bgBar.setPosition(x, y - 8);
        window.draw(bgBar);

        float ratio = (float)hp / maxHp;
        sf::RectangleShape hpBar(sf::Vector2f(32 * ratio, 5));
        hpBar.setFillColor(sf::Color::Green);
        hpBar.setPosition(x, y - 8);
        window.draw(hpBar);
    }
    bool reachedExit() const { return pathIndex >= pathCount; }

    string getType() const override { return "BasicEnemy"; }


};
