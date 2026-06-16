#pragma once
#include "Entity.h"
#include "Enemy.h"
#include"Variables.h"
class Tower : public Entity
{
protected:
    int   damage;
    float range;
    Enemy* target;
public:
    Tower(float x, float y, int damage, float range)
        : Entity(x, y, 200), damage(damage), range(range), target(nullptr) {
    }
    virtual void attack() = 0;
    void update() override {}
    virtual void update(Enemy* enemies[], int count) {}
    void setTarget(Enemy* e) { target = e; }
    bool inRange(Enemy* e) const
    {
        float dx = e->getX() - x;
        float dy = e->getY() - y;
        return (dx * dx + dy * dy) <= (range * range);
    }
    virtual ~Tower() {}
};


class CannonTower : public Tower
{
    sf::Texture texture;
    sf::Sprite sprite;

    float fireRate;
    sf::Clock fireClock;

    sf::SoundBuffer fireBuffer;
    sf::Sound fireSound;

public:

    CannonTower(float x, float y)
        : Tower(x, y, 60, 100.f), fireRate(2.0f)
    {
        if (!texture.loadFromFile("assets/CannonTower.jpg"))
        {

        }

        sprite.setTexture(texture);

        float sx = 64.f / texture.getSize().x;
        float sy = 64.f / texture.getSize().y;

        sprite.setScale(sx, sy);

        fireBuffer.loadFromFile("assets/gunshots.wav");
        fireSound.setBuffer(fireBuffer);
    }

    void attack() override
    {
        if (target == nullptr)
            return;

        if (!target->isAlive())
            return;

        if (!inRange(target))
            return;

        if (fireClock.getElapsedTime().asSeconds() >= fireRate)
        {
            target->takeDamage(damage);
            fireSound.play();
            takeDamage(40);
            fireClock.restart();
        }
    }

    void acquireTarget(Enemy* enemies[], int count)
    {
        if (target != nullptr && target->isAlive() && inRange(target))
            return;
        target = nullptr;
        for (int i = 0; i < count; i++)
        {
            if (enemies[i]->isAlive() && inRange(enemies[i]))
            {
                target = enemies[i];
                break;
            }
        }
    }

    void update(Enemy* enemies[], int count) override
    {

        if (!isAlive()) return;
        acquireTarget(enemies, count);
        if (target != nullptr && target->isAlive() && inRange(target))
        {
            attack();
        }
        else
        {
            fireSound.stop(); 
        }
    }

    void render(sf::RenderWindow& window) override
    {
       
        sf::CircleShape rangeCircle(range);

        rangeCircle.setOrigin(range, range);

        rangeCircle.setPosition(x + 32, y + 32);

        rangeCircle.setFillColor(sf::Color(0, 0, 0, 0));

        rangeCircle.setOutlineThickness(2);

        rangeCircle.setOutlineColor(sf::Color(255, 255, 255, 60));

        window.draw(rangeCircle);


        sprite.setPosition(x, y);

        window.draw(sprite);


        sf::RectangleShape bgBar(sf::Vector2f(64, 6));

        bgBar.setFillColor(sf::Color::Red);

        bgBar.setPosition(x, y - 10);

        window.draw(bgBar);


        float ratio = (float)hp / maxHp;

        sf::RectangleShape hpBar(sf::Vector2f(64 * ratio, 6));

        hpBar.setFillColor(sf::Color::Green);

        hpBar.setPosition(x, y - 10);

        window.draw(hpBar);
    }

    string getType() const override
    {
        return "CannonTower";
    }
};



class SniperTower : public Tower
{
    sf::Texture texture;
    sf::Sprite sprite;

    float fireRate;
    sf::Clock fireClock;

    sf::SoundBuffer fireBuffer;
    sf::Sound fireSound;

public:

    SniperTower(float x, float y)
        : Tower(x, y, 65, 150.f), fireRate(3.0f)
    {
        if (!texture.loadFromFile("assets/SniperTower.png"))
        {
        }

        sprite.setTexture(texture);

        float sx = 64.f / texture.getSize().x;
        float sy = 64.f / texture.getSize().y;

        sprite.setScale(sx, sy);
        fireBuffer.loadFromFile("assets/gunshots.wav");
        fireSound.setBuffer(fireBuffer);
    }

    void attack() override
    {
        if (target == nullptr)
            return;

        if (!target->isAlive())
            return;

        if (!inRange(target))
            return;

        if (fireClock.getElapsedTime().asSeconds() >= fireRate)
        {
            target->takeDamage(damage);
            fireSound.play();
            takeDamage(40);
            fireClock.restart();
        }
    }

    void acquireTarget(Enemy* enemies[], int count)
    {
        if (target != nullptr && target->isAlive() && inRange(target))
            return;

        target = nullptr;

        for (int i = 0; i < count; i++)
        {
            if (inRange(enemies[i]) && enemies[i]->isAlive())
            {
                target = enemies[i];
                break;
            }
        }
    }

    void update(Enemy* enemies[], int count)
    {
        if (!isAlive())
            return;

        acquireTarget(enemies, count);

        if (target != nullptr && target->isAlive() && inRange(target))
        {
            attack();
        }
        else
        {
            fireSound.stop();
        }
    }

    void render(sf::RenderWindow& window) override
    {
        if (!isAlive())
            return;

        sf::CircleShape rangeCircle(range);

        rangeCircle.setOrigin(range, range);

        rangeCircle.setPosition(x + 32, y + 32);

        rangeCircle.setFillColor(sf::Color(0, 0, 0, 0));

        rangeCircle.setOutlineThickness(2);

        rangeCircle.setOutlineColor(sf::Color(0, 255, 255, 80));

        window.draw(rangeCircle);

        sprite.setPosition(x, y);

        window.draw(sprite);

        sf::RectangleShape bgBar(sf::Vector2f(64, 6));

        bgBar.setFillColor(sf::Color::Red);

        bgBar.setPosition(x, y - 10);

        window.draw(bgBar);

        float ratio = (float)hp / maxHp;

        sf::RectangleShape hpBar(sf::Vector2f(64 * ratio, 6));

        hpBar.setFillColor(sf::Color::Green);

        hpBar.setPosition(x, y - 10);

        window.draw(hpBar);
    }

    string getType() const override
    {
        return "SniperTower";
    }
};



class MachineGunTower : public Tower
{
    sf::Texture texture;
    sf::Sprite sprite;

    float fireRate;
    sf::Clock fireClock;

    sf::SoundBuffer fireBuffer;
    sf::Sound fireSound;

public:

    MachineGunTower(float x, float y)
        : Tower(x, y, 8, 125.f), fireRate(0.2f)
    {
        if (!texture.loadFromFile("assets/MachineGunTower.png"))
        {
        }

        sprite.setTexture(texture);

        float sx = 64.f / texture.getSize().x;
        float sy = 64.f / texture.getSize().y;

        sprite.setScale(sx, sy);

        fireBuffer.loadFromFile("assets/gunshots.wav");
        fireSound.setBuffer(fireBuffer);
    }

    void attack() override
    {
        if (target == nullptr)
            return;

        if (!target->isAlive())
            return;

        if (!inRange(target))
            return;

        if (fireClock.getElapsedTime().asSeconds() >= fireRate)
        {
            target->takeDamage(damage);
            if (fireSound.getStatus() != sf::Sound::Playing)  
                fireSound.play();
            takeDamage(5);
            fireClock.restart();
        }
    }

    void acquireTarget(Enemy* enemies[], int count)
    {
        if (target != nullptr && target->isAlive() && inRange(target))
            return;

        target = nullptr;

        for (int i = 0; i < count; i++)
        {
            if (enemies[i]->isAlive() && inRange(enemies[i]))
            {
                target = enemies[i];
                break;
            }
        }
    }

    void update(Enemy* enemies[], int count)
    {
        if (!isAlive())
            return;

        acquireTarget(enemies, count);

        if (target != nullptr && target->isAlive() && inRange(target))
        {
            attack();
        }
        else
        {
            fireSound.stop();
        }
    }

    void render(sf::RenderWindow& window) override
    {
        if (!isAlive())
            return;

        sf::CircleShape rangeCircle(range);

        rangeCircle.setOrigin(range, range);

        rangeCircle.setPosition(x + 32, y + 32);

        rangeCircle.setFillColor(sf::Color(0, 0, 0, 0));

        rangeCircle.setOutlineThickness(2);

        rangeCircle.setOutlineColor(sf::Color(255, 255, 0, 80));

        window.draw(rangeCircle);

        sprite.setPosition(x, y);

        window.draw(sprite);

        sf::RectangleShape bgBar(sf::Vector2f(64, 6));

        bgBar.setFillColor(sf::Color::Red);

        bgBar.setPosition(x, y - 10);

        window.draw(bgBar);

        float ratio = (float)hp / maxHp;

        sf::RectangleShape hpBar(sf::Vector2f(64 * ratio, 6));

        hpBar.setFillColor(sf::Color::Green);

        hpBar.setPosition(x, y - 10);

        window.draw(hpBar);
    }

    string getType() const override
    {
        return "MachineGunTower";
    }
};


class SlowTower : public Tower
{
    sf::Texture texture;
    sf::Sprite sprite;
    float slowFactor;
    sf::Clock decayClock;
    float decayRate = 1.0f; 
    sf::SoundBuffer fireBuffer;
    sf::Sound fireSound;
public:

    SlowTower(float x, float y)
        : Tower(x, y, 999, 140.f), slowFactor(0.5f)
    {
        if (!texture.loadFromFile("assets/SlowTower.png"))
        {
        }

        sprite.setTexture(texture);

        float sx = 64.f / texture.getSize().x;
        float sy = 64.f / texture.getSize().y;

        sprite.setScale(sx, sy);

        fireBuffer.loadFromFile("assets/slow.mp3");
        fireSound.setBuffer(fireBuffer);
    }

    bool isSlowingAnyEnemy(Enemy* enemies[], int count)
    {
        for (int i = 0; i < count; i++)
        {
            if (enemies[i] == nullptr)
                continue;

            if (!enemies[i]->isAlive())
                continue;

            if (inRange(enemies[i]))
                return true;
        }
        return false;
    }

    void applySlow(Enemy* enemies[], int count)
    {
        for (int i = 0; i < count; i++)
        {
            if (enemies[i] == nullptr)
                continue;

            if (!enemies[i]->isAlive())
                continue;

            if (inRange(enemies[i]))
            {
                enemies[i]->setSpeed(enemies[i]->getBaseSpeed() * slowFactor);
               
            }
            else
            {
                enemies[i]->setSpeed(enemies[i]->getBaseSpeed());
                
            }
        }
    }

    void decayOnUse(Enemy* enemies[], int count)
    {
        if (!isSlowingAnyEnemy(enemies, count))
            return;

        if (decayClock.getElapsedTime().asSeconds() >= decayRate)
        {
            takeDamage(10);
            
            decayClock.restart();
        }
    }

    void update(Enemy* enemies[], int count)
    {
        if (!isAlive())
            return;

        applySlow(enemies, count);
        if (isSlowingAnyEnemy(enemies, count))
        {
            if (fireSound.getStatus() != sf::Sound::Playing)
            {
                fireSound.play();
            }
        }
        else
        {
            fireSound.stop();
        }

        decayOnUse(enemies, count);
    }

    void render(sf::RenderWindow& window) override
    {
        if (!isAlive())
            return;

        sf::CircleShape rangeCircle(range);

        rangeCircle.setOrigin(range, range);

        rangeCircle.setPosition(x + 32, y + 32);

        rangeCircle.setFillColor(sf::Color(0, 0, 0, 0));

        rangeCircle.setOutlineThickness(2);

        rangeCircle.setOutlineColor(sf::Color(0, 150, 255, 80));

        window.draw(rangeCircle);

        sprite.setPosition(x, y);

        window.draw(sprite);

        sf::RectangleShape bgBar(sf::Vector2f(64, 6));

        bgBar.setFillColor(sf::Color::Red);

        bgBar.setPosition(x, y - 10);

        window.draw(bgBar);

        float ratio = (float)hp / maxHp;

        sf::RectangleShape hpBar(sf::Vector2f(64 * ratio, 6));

        hpBar.setFillColor(sf::Color::Green);

        hpBar.setPosition(x, y - 10);

        window.draw(hpBar);
    }

    void attack() override {}

    string getType() const override
    {
        return "SlowTower";
    }
};


class BombTower : public Tower
{
    sf::Texture texture;
    sf::Sprite sprite;

    float fireRate;
    sf::Clock fireClock;

    float explosionRadius;
    int chainCount;

    sf::Clock explosionClock;
    bool exploding;
    float explosionVisualRadius;
    sf::Vector2f explosionCenter;

    sf::SoundBuffer fireBuffer;
    sf::Sound fireSound;

public:

    BombTower(float x, float y)
        : Tower(x, y, 30,140.f),
        fireRate(2.5f),
        explosionRadius(70.f),
        chainCount(3),
        exploding(false),
        explosionVisualRadius(0.f),
        explosionCenter(0.f, 0.f)
    {
        if (!texture.loadFromFile("assets/BombTower.png"))
        {
        }

        sprite.setTexture(texture);

        float sx = 64.f / texture.getSize().x;
        float sy = 64.f / texture.getSize().y;

        sprite.setScale(sx, sy);
        fireBuffer.loadFromFile("assets/bomb.ogg");
        fireSound.setBuffer(fireBuffer);
    }

    void attack() override
    {
        return;
    }

    Enemy* findTarget(Enemy* enemies[], int count)
    {
        for (int i = 0; i < count; i++)
        {
            if (enemies[i] == nullptr)
                continue;

            if (!enemies[i]->isAlive())
                continue;

            if (inRange(enemies[i]))
                return enemies[i];
        }

        return nullptr;
    }

    void explode(Enemy* enemies[], int count, Enemy* centerEnemy)
    {
        float cx = centerEnemy->getX();
        float cy = centerEnemy->getY();

        for (int i = 0; i < count; i++)
        {
            if (enemies[i] == nullptr)
                continue;

            if (!enemies[i]->isAlive())
                continue;

            float dx = enemies[i]->getX() - cx;
            float dy = enemies[i]->getY() - cy;

            float dist2 = dx * dx + dy * dy;

            if (dist2 <= explosionRadius * explosionRadius)
            {
                enemies[i]->takeDamage(damage);
                fireSound.play();
            }
        }
    }

    void chainBomb(Enemy* enemies[], int count, Enemy* start)
    {
        Enemy* current = start;

        for (int c = 0; c < chainCount; c++)
        {
            if (current == nullptr)
                return;

            explode(enemies, count, current);

            explosionCenter = sf::Vector2f(current->getX(), current->getY());
            exploding = true;
            explosionVisualRadius = 0.f;
            explosionClock.restart();

            Enemy* next = nullptr;
            float bestDist = 999999.f;

            for (int i = 0; i < count; i++)
            {
                if (enemies[i] == nullptr)
                    continue;

                if (!enemies[i]->isAlive())
                    continue;

                if (enemies[i] == current)
                    continue;

                float dx = enemies[i]->getX() - current->getX();
                float dy = enemies[i]->getY() - current->getY();

                float dist = dx * dx + dy * dy;

                if (dist < bestDist && dist <= range * range)
                {
                    bestDist = dist;
                    next = enemies[i];
                }
            }

            current = next;
        }
    }

    void update(Enemy* enemies[], int count)
    {
        if (!isAlive())
            return;

        if (exploding)
        {
            explosionVisualRadius += 6.f;

            if (explosionVisualRadius > explosionRadius)
            {
                exploding = false;
            }
        }

        if (fireClock.getElapsedTime().asSeconds() >= fireRate)
        {
            Enemy* target = findTarget(enemies, count);

            if (target != nullptr)
            {
                chainBomb(enemies, count, target);
                takeDamage(30);
            }

            fireClock.restart();
        }
    }

    void render(sf::RenderWindow& window) override
    {
        if (!isAlive())
            return;

        sf::CircleShape rangeCircle(range);

        rangeCircle.setOrigin(range, range);

        rangeCircle.setPosition(x + 32, y + 32);

        rangeCircle.setFillColor(sf::Color(0, 0, 0, 0));

        rangeCircle.setOutlineThickness(2);

        rangeCircle.setOutlineColor(sf::Color(255, 120, 0, 80));

        window.draw(rangeCircle);

        sprite.setPosition(x, y);

        window.draw(sprite);

        if (exploding)
        {
            sf::CircleShape explosion(explosionVisualRadius);

            explosion.setOrigin(explosionVisualRadius, explosionVisualRadius);

            explosion.setPosition(explosionCenter);

            explosion.setFillColor(sf::Color(255, 120, 0, 40));

            explosion.setOutlineThickness(2);

            explosion.setOutlineColor(sf::Color(255, 200, 0, 120));

            window.draw(explosion);
        }

        sf::RectangleShape bgBar(sf::Vector2f(64, 6));

        bgBar.setFillColor(sf::Color::Red);

        bgBar.setPosition(x, y - 10);

        window.draw(bgBar);

        float ratio = (float)hp / maxHp;

        sf::RectangleShape hpBar(sf::Vector2f(64 * ratio, 6));

        hpBar.setFillColor(sf::Color::Green);

        hpBar.setPosition(x, y - 10);

        window.draw(hpBar);
    }

    string getType() const override
    {
        return "BombTower";
    }
};