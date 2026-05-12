#pragma once
#include"Entity.h"
#include"Variables.h"
class Enemy :public Entity {
protected:
    float speed;
    int reward;
    int pathIndex;
    float baseSpeed;
public:
    Enemy(float x, float y, int hp, float speed, int reward)
        : Entity(x, y, hp), speed(speed), reward(reward), pathIndex(0),baseSpeed(speed) {
    }

    virtual void move() = 0;
    virtual bool reachedExit() const = 0;

    void update() override { move(); }

    int   getReward()    const { return reward; }
    float getSpeed()     const { return speed; }
    void  setSpeed(float s) { speed = s; }
    float getBaseSpeed() const
    {
        return baseSpeed;
    }

    virtual ~Enemy() {}
};
class BasicEnemy :public Enemy {
    sf::Texture texture;
    sf::Sprite sprite;
    WayPoint* path;   //A pointer that points to the WayPoints array
    int pathCount;    //Shows how many WayPoints
public:
    BasicEnemy(WayPoint* path, int pathCount) :Enemy(path[0].x, path[0].y, 100, 1.0f, 10)
        , path(path), pathCount(pathCount)
    {
        if (!texture.loadFromFile("assets/BasicEnemy.png"))
        {

        }
        sprite.setTexture(texture);
        float sx = 40.f / texture.getSize().x;
        float sy = 40.f / texture.getSize().y;
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

        sf::RectangleShape bgBar(sf::Vector2f(40, 5));
        bgBar.setFillColor(sf::Color::Red);
        bgBar.setPosition(x, y - 8);
        window.draw(bgBar);

        float ratio = (float)hp / maxHp;
        sf::RectangleShape hpBar(sf::Vector2f(40 * ratio, 5));
        hpBar.setFillColor(sf::Color::Green);
        hpBar.setPosition(x, y - 8);
        window.draw(hpBar);
    }
    bool reachedExit() const { return pathIndex >= pathCount; }

    string getType() const override { return "BasicEnemy"; }
};

class FastEnemy :public Enemy {
    sf::Texture texture;
    sf::Sprite sprite;
    WayPoint* path;
    int pathCount;
public:
    FastEnemy(WayPoint* path, int pathCount) :Enemy(path[0].x, path[0].y, 50, 1.5f, 20)
        , path(path), pathCount(pathCount)
    {
        if (!texture.loadFromFile("assets/FastEnemy.png"))
        {

        }
        sprite.setTexture(texture);
        float sx = 47.f / texture.getSize().x;
        float sy = 47.f / texture.getSize().y;
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
    void render(sf::RenderWindow& window)override
    {
        sprite.setPosition(x, y);
        window.draw(sprite);
        sf::RectangleShape bgBar(sf::Vector2f(43, 5));
        bgBar.setFillColor(sf::Color::Red);
        bgBar.setPosition(x, y - 8);
        window.draw(bgBar);

        float ratio = (float)hp / maxHp;
        sf::RectangleShape hpBar(sf::Vector2f(43 * ratio, 5));
        hpBar.setFillColor(sf::Color::Green);
        hpBar.setPosition(x, y - 8);
        window.draw(hpBar);
    }
    bool reachedExit() const { return pathIndex >= pathCount; }

    string getType() const override { return "FastEnemy"; }

};
class TankEnemy :public Enemy {
    sf::Texture texture;
    sf::Sprite sprite;
    WayPoint* path;
    int pathCount;
public:
    TankEnemy(WayPoint* path, int pathCount) :Enemy(path[0].x, path[0].y, 350, 0.7f, 50)
        , path(path), pathCount(pathCount)
    {
        if (!texture.loadFromFile("assets/TankEnemy.png"))
        {

        }
        sprite.setTexture(texture);
        float sx = 47.f / texture.getSize().x;
        float sy = 47.f / texture.getSize().y;
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
    void render(sf::RenderWindow& window)override
    {
        sprite.setPosition(x, y);
        window.draw(sprite);
        sf::RectangleShape bgBar(sf::Vector2f(40, 5));
        bgBar.setFillColor(sf::Color::Red);
        bgBar.setPosition(x, y - 8);
        window.draw(bgBar);

        float ratio = (float)hp / maxHp;
        sf::RectangleShape hpBar(sf::Vector2f(40 * ratio, 5));
        hpBar.setFillColor(sf::Color::Green);
        hpBar.setPosition(x, y - 8);
        window.draw(hpBar);
    }
    bool reachedExit() const { return pathIndex >= pathCount; }

    string getType() const override { return "TankEnemy"; }

};
class FlyingEnemy : public Enemy {
    sf::Texture texture;
    sf::Sprite sprite;
    float destX;
    float destY;
    bool arrived;

public:

    FlyingEnemy(float startX, float startY, float destX, float destY)
        : Enemy(startX, startY, 60, 1.8f, 35),
        destX(destX), destY(destY), arrived(false)
    {
        if (!texture.loadFromFile("assets/FlyingEnemyS2.png"))
        {
        }
        sprite.setTexture(texture);
        float sx = 50.f / texture.getSize().x;
        float sy = 50.f / texture.getSize().y;
        sprite.setScale(sx, sy);
    }

    void move() override
    {
        if (arrived) return;


        float dx = destX - x;
        float dy = destY - y;
        float dist = sqrt(dx * dx + dy * dy);

        if (dist <= speed)
        {
            x = destX;
            y = destY;
            arrived = true;
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


        sf::RectangleShape bgBar(sf::Vector2f(45, 5));
        bgBar.setFillColor(sf::Color::Red);
        bgBar.setPosition(x, y - 8);
        window.draw(bgBar);

        float ratio = (float)hp / maxHp;
        sf::RectangleShape hpBar(sf::Vector2f(45 * ratio, 5));
        hpBar.setFillColor(sf::Color::Cyan);
        hpBar.setPosition(x, y - 8);
        window.draw(hpBar);
    }

    bool reachedExit() const { return arrived; }
    string getType() const override { return "FlyingEnemy"; }
};

class OmegaEnemy : public Enemy {
    sf::Texture texture;
    sf::Sprite sprite;
    WayPoint* path;
    int pathCount;

public:
    OmegaEnemy(WayPoint* path, int pathCount)
        : Enemy(path[0].x, path[0].y, 500, 0.5f, 100),
        path(path), pathCount(pathCount)
    {
        if (!texture.loadFromFile("assets/Omega.png"))
        {
        }
        sprite.setTexture(texture);
        float sx = 45.f / texture.getSize().x;
        float sy = 45.f / texture.getSize().y;
        sprite.setScale(sx, sy);
    }

    void move() override
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


    void takeDamage(int dmg) override
    {
        hp -= dmg;
        if (hp <= 0) { hp = 0; return; }

        float ratio = (float)hp / maxHp;

        if (ratio <= 0.25f) speed = baseSpeed = 3.2f;
        else if (ratio <= 0.50f) speed = baseSpeed = 2.2f;
        else if (ratio <= 0.75f) speed = baseSpeed = 1.5f;
        else                     speed = baseSpeed = 0.5f;
    }

    void render(sf::RenderWindow& window) override
    {
        if (!isAlive()) return;
        sprite.setPosition(x, y);
        window.draw(sprite);


        sf::RectangleShape bgBar(sf::Vector2f(48, 5));
        bgBar.setFillColor(sf::Color::Red);
        bgBar.setPosition(x - 8, y - 12);
        window.draw(bgBar);

        float ratio = (float)hp / maxHp;
        sf::RectangleShape hpBar(sf::Vector2f(48 * ratio, 5));


        if (ratio <= 0.25f) hpBar.setFillColor(sf::Color::Red);
        else if (ratio <= 0.50f) hpBar.setFillColor(sf::Color(255, 100, 0));
        else if (ratio <= 0.75f) hpBar.setFillColor(sf::Color(160, 32, 240));
        else                     hpBar.setFillColor(sf::Color(160, 32, 240));

        hpBar.setPosition(x - 8, y - 12);
        window.draw(hpBar);
    }

    bool reachedExit() const { return pathIndex >= pathCount; }
    string getType() const override { return "OmegaEnemy"; }
};
