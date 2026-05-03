#include"Entity.h"
#include"Enemy.h"
#include"Tower.h"
#include"Globals.h"


Wave waves[totalWaves];

void SetAttackPath()
{
    for (int i = 0;i < 9;i++)
    {
        grid[6][i] = 1;
        grid[7][i] = 1;
    }
    for (int i = 7;i < 19;i++)
    {
        grid[i][7] = 1;
        grid[i][8] = 1;
    }
    for (int i = 8;i < 17;i++)
    {
        grid[17][i] = 1;
        grid[18][i] = 1;
    }
    for (int i = 9;i < 18;i++)
    {
        grid[i][15] = 1;
        grid[i][16] = 1;
    }
    for (int i = 15;i < 26;i++)
    {
        grid[9][i] = 1;
        grid[10][i] = 1;
    }
    for (int i = 9;i < 19;i++)
    {
        grid[i][26] = 1;
        grid[i][25] = 1;
    }
    for (int i = 25;i < 35;i++)
    {
        grid[19][i] = 1;
        grid[20][i] = 1;
    }

}
void SetFences()
{


    for (int j = 0; j < 35; j++)
    {
        grid[0][j] = 2;
        grid[rows - 1][j] = 2;
    }

    for (int i = 0;i < 24;i++)
    {
        grid[i][35] = 2;
    }


    for (int i = 0; i < rows; i++)
    {
        grid[i][0] = 2;
    }
}

WayPoint waypoints[wayPointsCount] =
{
    { 0 * 32 + 16, 6.5f * 32 },
    { 7.5f * 32, 6.5f * 32 },
    { 7.5f * 32, 17.5f * 32 },
    { 15.5f * 32, 17.5f * 32 },
    { 15.5f * 32, 9.5f * 32 },
    { 25.5f * 32, 9.5f * 32 },
    { 25.5f * 32, 19.5f * 32 },
    { 34 * 32 + 16, 19.5f * 32 }
};


void SetWaves()
{
    waves[0].enemyCount = 5;
    waves[0].spawnInterval = 2.0f;
    for (int i = 0;i < 5;i++)
    {
        waves[0].enemies[i] = new BasicEnemy(waypoints, wayPointsCount);
    }
    waves[1].enemyCount = 8;
    waves[1].spawnInterval = 1.8f;
    for (int i = 0;i < 4;i++)
    {
        waves[1].enemies[i] = new BasicEnemy(waypoints, wayPointsCount);
    }
    for (int i = 4;i < 8;i++)
    {
        waves[1].enemies[i] = new FastEnemy(waypoints, wayPointsCount);
    }
    waves[2].enemyCount = 10;
    waves[2].spawnInterval = 1.5f;
    for (int i = 0;i < 3;i++)
    {
        waves[2].enemies[i] = new BasicEnemy(waypoints, wayPointsCount);
    }
    for (int i = 3;i < 6;i++)
    {
        waves[2].enemies[i] = new FastEnemy(waypoints, wayPointsCount);
    }
    for (int i = 6;i < 10;i++)
    {
        waves[2].enemies[i] = new TankEnemy(waypoints, wayPointsCount);
    }

    waves[3].enemyCount = 12;
    waves[3].spawnInterval = 1.2f;
    for (int i = 0; i < 3; i++)
        waves[3].enemies[i] = new BasicEnemy(waypoints, wayPointsCount);
    for (int i = 3; i < 6; i++)
        waves[3].enemies[i] = new FastEnemy(waypoints, wayPointsCount);
    for (int i = 6; i < 9; i++)
        waves[3].enemies[i] = new TankEnemy(waypoints, wayPointsCount);
    for (int i = 9; i < 12; i++)
        waves[3].enemies[i] = new FlyingEnemy(
            waypoints[0].x, waypoints[0].y,
            waypoints[7].x, waypoints[7].y);

    waves[4].enemyCount = 15;
    waves[4].spawnInterval = 1.0f;
    for (int i = 0; i < 3; i++)
        waves[4].enemies[i] = new BasicEnemy(waypoints, wayPointsCount);
    for (int i = 3; i < 6; i++)
        waves[4].enemies[i] = new FastEnemy(waypoints, wayPointsCount);
    for (int i = 6; i < 9; i++)
        waves[4].enemies[i] = new TankEnemy(waypoints, wayPointsCount);
    for (int i = 9; i < 12; i++)
        waves[4].enemies[i] = new FlyingEnemy(
            waypoints[0].x, waypoints[0].y,
            waypoints[7].x, waypoints[7].y);
    for (int i = 12;i < 15;i++)
    {
        waves[4].enemies[i] = new OmegaEnemy(waypoints, wayPointsCount);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Tower Defense Rush", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    SetAttackPath();
    SetFences();
    SetWaves();

    sf::Texture grassTexture;
    grassTexture.loadFromFile("assets/grass.png");
    grassTexture.setRepeated(true);
    sf::Texture mudTexture;
    mudTexture.loadFromFile("assets/mud.png");
    mudTexture.setRepeated(true);
    sf::Texture brickTexture;
    brickTexture.loadFromFile("assets/brick.png");
    sf::Sprite brickSprite;
    brickSprite.setTexture(brickTexture);
    float scaleX = (float)TileSize / brickTexture.getSize().x;
    float scaleY = (float)TileSize / brickTexture.getSize().y;
    brickSprite.setScale(scaleX, scaleY);

    int currentWave = 0;
    sf::Clock spawnClock;
    Enemy* activeEnemies[MaxEnemiesPerWave];
    int activeCount = 0;
   

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
        }

        sf::RectangleShape tile(sf::Vector2f(TileSize, TileSize));
        window.clear(sf::Color(30, 30, 30));
        for (int i = 0;i < rows;i++)
        {
            for (int j = 0;j < cols;j++)
            {
                tile.setPosition(j * TileSize, i * TileSize);
                if (grid[i][j] == 1)
                {
                    tile.setTexture(&mudTexture);

                    tile.setFillColor(sf::Color(139, 115, 85));
                }
                else if (grid[i][j] == 2)
                {
                    brickSprite.setPosition(j * TileSize, i * TileSize);

                    window.draw(brickSprite);
                    continue;
                }
                else
                {
                    tile.setTexture(&grassTexture);
                    tile.setFillColor(sf::Color::White);
                }
                window.draw(tile);
            }
            
      
        }
        Wave& wave = waves[currentWave];
        if (currentWave < totalWaves)
        {
            Wave& wave = waves[currentWave];

            if (wave.currentSpawn < wave.enemyCount)
            {
                if (spawnClock.getElapsedTime().asSeconds() >= wave.spawnInterval)
                {
                    activeEnemies[activeCount] = wave.enemies[wave.currentSpawn];
                    activeCount++;
                    wave.currentSpawn++;
                    spawnClock.restart();
                }
            }

            if (wave.currentSpawn >= wave.enemyCount && activeCount == 0)
                currentWave++;
        }
        if (wave.currentSpawn < wave.enemyCount)
        {
            if (spawnClock.getElapsedTime().asSeconds() >= wave.spawnInterval)
            {
                activeEnemies[activeCount] = wave.enemies[wave.currentSpawn];
                activeCount++;
                wave.currentSpawn++;
                spawnClock.restart();
            }
        }


        for (int i = 0; i < activeCount; i++)
        {
            if (activeEnemies[i] != nullptr)
            {
                activeEnemies[i]->update();
                activeEnemies[i]->render(window);
            }
            bool shouldRemove = false;

            if (!activeEnemies[i]->isAlive() || activeEnemies[i]->reachedExit())
                shouldRemove = true;

            if (shouldRemove)
            {
                // swap with last element and reduce count
                activeEnemies[i] = activeEnemies[activeCount - 1];
                activeEnemies[activeCount - 1] = nullptr;
                activeCount--;
                i--;  // recheck this index
            }

        }
        if (wave.currentSpawn >= wave.enemyCount && activeCount == 0)
        {
            currentWave++;
        }

   
        window.display();
    }
    return 0;
}
