#include"Entity.h"
#include"Enemy.h"
#include"Tower.h"
#include"Variables.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
using namespace std;

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

bool isValidTowerPlacement(int row, int col)
{
  
    if (row < 0 || row >= rows || col < 0 || col >= cols)
        return false;

   
    if (grid[row][col] != 0)
        return false;

    return true;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Tower Defense Rush", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    sf::View gameView(sf::FloatRect(0.f, 0.f, (float)(cols * TileSize), (float)(rows * TileSize)));
    window.setView(gameView);

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
   
    sf::Texture coinTexture;
    coinTexture.loadFromFile("assets/coin.png");

    sf::Sprite coinSprite;
    coinSprite.setTexture(coinTexture);
    float desiredSize = 40.f;
    coinSprite.setScale(desiredSize / coinTexture.getSize().x,
        desiredSize / coinTexture.getSize().y);

    sf::Font font;
    font.loadFromFile("assets/arial.ttf");

    sf::Text coinText;
    coinText.setFont(font);
    coinText.setCharacterSize(24);
    coinText.setFillColor(sf::Color::Yellow);

    sf::Texture heartTexture;
    heartTexture.loadFromFile("assets/heart.png");

    sf::Sprite heartSprite;
    heartSprite.setTexture(heartTexture);
    float heartSize = 40.f;
    heartSprite.setScale(heartSize / heartTexture.getSize().x, heartSize / heartTexture.getSize().y);

    sf::Texture smallHeartTexture;
    smallHeartTexture.loadFromFile("assets/heart.png");

    sf::Sprite smallHeartSprite;
    smallHeartSprite.setTexture(smallHeartTexture);
    smallHeartSprite.setScale(
        25.f / smallHeartTexture.getSize().x,
        25.f / smallHeartTexture.getSize().y);

    sf::SoundBuffer winBuffer, loseBuffer, startBuffer;
    sf::Sound winSound, loseSound, startSound;

    sf::Texture winTexture, loseTexture, startTexture;
    sf::Sprite winSprite, loseSprite, startSprite;

    startBuffer.loadFromFile("assets/gameStart.wav");
    winBuffer.loadFromFile("assets/gameWin.wav");
    loseBuffer.loadFromFile("assets/gameOver.mp3");

    startSound.setBuffer(startBuffer);
    winSound.setBuffer(winBuffer);
    loseSound.setBuffer(loseBuffer);

    startTexture.loadFromFile("assets/play.png");
    winTexture.loadFromFile("assets/gameWinImg.jpg");
    loseTexture.loadFromFile("assets/gameOverImg.png");

    startSprite.setTexture(startTexture);
    winSprite.setTexture(winTexture);
    loseSprite.setTexture(loseTexture);

    sf::RectangleShape lifeBox(sf::Vector2f(200, 60));
    lifeBox.setPosition(1160, 520);
    lifeBox.setFillColor(sf::Color(150, 20, 20));
    lifeBox.setOutlineThickness(3);
    lifeBox.setOutlineColor(sf::Color::White);

    sf::Text lifeText;
    lifeText.setFont(font);
    lifeText.setCharacterSize(20);
    lifeText.setFillColor(sf::Color::White);
    lifeText.setString("Buy a Life - 500");
    lifeText.setPosition(1200, 535);
    smallHeartSprite.setPosition(1168, 535);

    sf::Text livesText;
    livesText.setFont(font);
    livesText.setCharacterSize(24);
    livesText.setFillColor(sf::Color::Red);

    sf::RectangleShape cannonBox(sf::Vector2f(200, 60));
    cannonBox.setPosition(1160, 120);
    cannonBox.setFillColor(sf::Color(80, 80, 80));
    cannonBox.setOutlineThickness(3);
    cannonBox.setOutlineColor(sf::Color::White);

    sf::Text cannonText;
    cannonText.setFont(font);
    cannonText.setCharacterSize(20);
    cannonText.setFillColor(sf::Color::White);
    cannonText.setString("Cannon Tower - 100");
    cannonText.setPosition(1168, 135);

    

    sf::RectangleShape sniperBox(sf::Vector2f(200, 60));
    sniperBox.setPosition(1160, 200);
    sniperBox.setFillColor(sf::Color(50, 70, 120));
    sniperBox.setOutlineThickness(3);
    sniperBox.setOutlineColor(sf::Color::White);

    sf::Text sniperText;
    sniperText.setFont(font);
    sniperText.setCharacterSize(20);
    sniperText.setFillColor(sf::Color::White);
    sniperText.setString("Sniper Tower - 150");
    sniperText.setPosition(1170, 215);

   

    sf::RectangleShape machineBox(sf::Vector2f(200, 60));
    machineBox.setPosition(1160, 280);
    machineBox.setFillColor(sf::Color(120, 90, 40));
    machineBox.setOutlineThickness(3);
    machineBox.setOutlineColor(sf::Color::White);

    sf::Text machineText;
    machineText.setFont(font);
    machineText.setCharacterSize(18);
    machineText.setFillColor(sf::Color::White);
    machineText.setString("Machine Gun - 120");
    machineText.setPosition(1170, 295);

    

    sf::RectangleShape slowBox(sf::Vector2f(200, 60));
    slowBox.setPosition(1160, 360);
    slowBox.setFillColor(sf::Color(40, 100, 150));
    slowBox.setOutlineThickness(3);
    slowBox.setOutlineColor(sf::Color::White);

    sf::Text slowText;
    slowText.setFont(font);
    slowText.setCharacterSize(20);
    slowText.setFillColor(sf::Color::White);
    slowText.setString("Slow Tower - 130");
    slowText.setPosition(1170, 375);

   

    sf::RectangleShape bombBox(sf::Vector2f(200, 60));
    bombBox.setPosition(1160, 440);
    bombBox.setFillColor(sf::Color(150, 60, 60));
    bombBox.setOutlineThickness(3);
    bombBox.setOutlineColor(sf::Color::White);

    sf::Text bombText;
    bombText.setFont(font);
    bombText.setCharacterSize(20);
    bombText.setFillColor(sf::Color::White);
    bombText.setString("Bomb Tower - 200");
    bombText.setPosition(1170, 455);

   

    int currentWave = 0;
    sf::Clock spawnClock;
    Enemy* activeEnemies[MaxEnemiesPerWave];
    int activeCount = 0;
    int gameState = 0;
    float endAnimScale = 0.f;

    sf::Clock startClock;
    float startScale = 0.f;

    float centerX = gameView.getCenter().x;
    float centerY = gameView.getCenter().y;
    startSound.play();

    while (window.isOpen())
    {
        bool showIntro = startClock.getElapsedTime().asSeconds() < 6.f;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                
                sf::Vector2f mousePos = window.mapPixelToCoords(
                    sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                

                    bool clickedOnBox = false;

                  
                    if (cannonBox.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        if (coins >= 100)
                        {
                            selectedTower = "Cannon";
                            placingTower = true;
                            selectedCost = 100;
                        }

                        clickedOnBox = true;
                    }

                  
                    else if (sniperBox.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        if (coins >= 150)
                        {
                            selectedTower = "Sniper";
                            placingTower = true;
                            selectedCost = 150;
                        }

                        clickedOnBox = true;
                    }

                  
                    else if (machineBox.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        if (coins >= 120)
                        {
                            selectedTower = "Machine";
                            placingTower = true;
                            selectedCost = 120;
                        }

                        clickedOnBox = true;
                    }

                
                    else if (slowBox.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        if (coins >= 130)
                        {
                            selectedTower = "Slow";
                            placingTower = true;
                            selectedCost = 130;
                        }

                        clickedOnBox = true;
                    }

                   
                    else if (bombBox.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        if (coins >= 200)
                        {
                            selectedTower = "Bomb";
                            placingTower = true;
                            selectedCost = 200;
                        }

                        clickedOnBox = true;
                    }

                    else if (lifeBox.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        if (coins >= 500)
                        {
                            coins -= 500;
                            lives++;
                        }

                        clickedOnBox = true;
                    }

                   
                    if (placingTower && !clickedOnBox)
                    {
                        int col = mousePos.x / TileSize;
                        int row = mousePos.y / TileSize;

                       
                        if (mousePos.x >= 36 * TileSize)
                        {
                            placingTower = false;   
                            selectedTower = "";
                            continue;              
                        }

                        if (isValidTowerPlacement(row, col))
                        {
                            if (selectedTower == "Cannon")
                                placedTowers[towerCount] = new CannonTower(col * TileSize, row * TileSize);

                            else if (selectedTower == "Sniper")
                                placedTowers[towerCount] = new SniperTower(col * TileSize, row * TileSize);

                            else if (selectedTower == "Machine")
                                placedTowers[towerCount] = new MachineGunTower(col * TileSize, row * TileSize);

                            else if (selectedTower == "Slow")
                                placedTowers[towerCount] = new SlowTower(col * TileSize, row * TileSize);

                            else if (selectedTower == "Bomb")
                                placedTowers[towerCount] = new BombTower(col * TileSize, row * TileSize);

                            towerCount++;

                            grid[row][col] = 3; 

                            coins -= selectedCost;

                            placingTower = false;
                            selectedTower = "";
                        }
                    }
            }
        }
        sf::RectangleShape panel(sf::Vector2f(cols * TileSize - 36 * TileSize, rows * TileSize));
        panel.setPosition(36 * TileSize, 0);
        panel.setFillColor(sf::Color(50, 50, 50));  
      

        sf::RectangleShape tile(sf::Vector2f(TileSize, TileSize));
       
        window.clear(sf::Color(30, 30, 30));
        window.draw(panel);
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

        if (showIntro)
        {
            if (startScale < 1.f)
                startScale += 0.02f;

            startSprite.setOrigin(
                startSprite.getTexture()->getSize().x / 2.f,
                startSprite.getTexture()->getSize().y / 2.f
            );

            startSprite.setPosition(centerX, centerY);

            startSprite.setScale(startScale, startScale);

            window.draw(startSprite);

            window.display();

            continue;
        }

        if (gameState != 0)
        {
            //window.clear(sf::Color::Black);

            if (endAnimScale < 1.f)
                endAnimScale += 0.02f;

            if (gameState == 1)
            {
                winSprite.setOrigin(
                    winSprite.getTexture()->getSize().x / 2.f,
                    winSprite.getTexture()->getSize().y / 2.f
                );

                winSprite.setPosition(centerX, centerY);

                winSprite.setScale(endAnimScale, endAnimScale);

                window.draw(winSprite);
            }

            if (gameState == 2)
            {
                loseSprite.setOrigin(
                    loseSprite.getTexture()->getSize().x / 2.f,
                    loseSprite.getTexture()->getSize().y / 2.f
                );

                loseSprite.setPosition(centerX, centerY);

                loseSprite.setScale(endAnimScale, endAnimScale);

                window.draw(loseSprite);
            }

            window.display();

            continue;
        }
        Wave* wave = nullptr;

        if (currentWave < totalWaves && gameState == 0)
        {
            wave = &waves[currentWave];
            if (wave->currentSpawn < wave->enemyCount)    //agar current enemy ka number less ho total enemies of the wave se
            {
                if (spawnClock.getElapsedTime().asSeconds() >= wave->spawnInterval)
                    //checking if enough time has passed till last spawn
                {
                    activeEnemies[activeCount] = wave->enemies[wave->currentSpawn];
                    activeCount++;
                    wave->currentSpawn++;
                    spawnClock.restart();
                }
            }

        }

        for (int i = 0; i < activeCount; i++)
        {
            if (activeEnemies[i] == nullptr) continue;

            activeEnemies[i]->update();

            bool shouldRemove = false;

            if (!activeEnemies[i]->isAlive())
            {
                if (dynamic_cast<BasicEnemy*>(activeEnemies[i]))       coins += 50;
                else if (dynamic_cast<FastEnemy*>(activeEnemies[i]))   coins += 70;
                else if (dynamic_cast<TankEnemy*>(activeEnemies[i]))   coins += 120;
                else if (dynamic_cast<FlyingEnemy*>(activeEnemies[i])) coins += 100;
                else if (dynamic_cast<OmegaEnemy*>(activeEnemies[i]))  coins += 300;
                shouldRemove = true;
            }
            else if (activeEnemies[i]->reachedExit())
            {
                lives--;
                shouldRemove = true;
            }

            if (shouldRemove)
            {
                activeEnemies[i] = activeEnemies[activeCount - 1];
                activeEnemies[activeCount - 1] = nullptr;
                activeCount--;
                i--;
            }
            else
            {
                activeEnemies[i]->render(window); 
            }

            if (lives <= 0 && gameState == 0)
            {
                gameState = 2;
                loseSound.play();
            }
        }

        if (wave->currentSpawn >= wave->enemyCount && activeCount == 0)
        {
            currentWave++;
        }
        if (currentWave >= totalWaves && gameState == 0)
        {
            gameState = 1;
            winSound.play();
        }

        if (placingTower)
        {
            sf::CircleShape preview(20);

            preview.setFillColor(sf::Color(255, 255, 255, 120));

            if (placingTower)
            {
                sf::Vector2f worldMouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                preview.setPosition(worldMouse.x - 20, worldMouse.y - 20);
                window.draw(preview);
            }
        }
       

        coinText.setString(std::to_string(coins));

        coinText.setPosition(1212, 22);  
        
        window.draw(coinText);
        
        coinSprite.setPosition(1158, 20);
        
        window.draw(coinSprite);
        
        heartSprite.setPosition(1280, 22);
        
        window.draw(heartSprite);
        
        livesText.setString(std::to_string(lives));
        
        livesText.setPosition(1322, 22);
        
        window.draw(livesText);
        
        cannonBox.setOutlineColor(sf::Color::White);
        
        sniperBox.setOutlineColor(sf::Color::White);
        
        machineBox.setOutlineColor(sf::Color::White);
        
        slowBox.setOutlineColor(sf::Color::White);
        
        bombBox.setOutlineColor(sf::Color::White);
        
        if (selectedTower == "Cannon")
        
            cannonBox.setOutlineColor(sf::Color::Yellow);

        if (selectedTower == "Sniper")
            sniperBox.setOutlineColor(sf::Color::Yellow);

        if (selectedTower == "Machine")
            machineBox.setOutlineColor(sf::Color::Yellow);

        if (selectedTower == "Slow")
            slowBox.setOutlineColor(sf::Color::Yellow);

        if (selectedTower == "Bomb")
            bombBox.setOutlineColor(sf::Color::Yellow);

        for (int i = 0; i < towerCount; i++)
        {
            placedTowers[i]->update(activeEnemies, activeCount);
            placedTowers[i]->render(window);
            if (!placedTowers[i]->isAlive())
            {
               
                int col = (int)(placedTowers[i]->getX() / TileSize);
                int row = (int)(placedTowers[i]->getY() / TileSize);
                grid[row][col] = 0;

                delete placedTowers[i];

               
                placedTowers[i] = placedTowers[towerCount - 1];
                placedTowers[towerCount - 1] = nullptr;
                towerCount--;
                i--;
            }
        }

        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        
        cannonBox.setOutlineColor(sf::Color::White);
        sniperBox.setOutlineColor(sf::Color::White);
        machineBox.setOutlineColor(sf::Color::White);
        slowBox.setOutlineColor(sf::Color::White);
        bombBox.setOutlineColor(sf::Color::White);
        lifeBox.setOutlineColor(sf::Color::White);

        if (lifeBox.getGlobalBounds().contains(mousePos.x, mousePos.y))
            lifeBox.setOutlineColor(sf::Color::Cyan);

      
        if (cannonBox.getGlobalBounds().contains(mousePos.x, mousePos.y))
            cannonBox.setOutlineColor(sf::Color::Cyan);

        if (sniperBox.getGlobalBounds().contains(mousePos.x, mousePos.y))
            sniperBox.setOutlineColor(sf::Color::Cyan);

        if (machineBox.getGlobalBounds().contains(mousePos.x, mousePos.y))
            machineBox.setOutlineColor(sf::Color::Cyan);

        if (slowBox.getGlobalBounds().contains(mousePos.x, mousePos.y))
            slowBox.setOutlineColor(sf::Color::Cyan);

        if (bombBox.getGlobalBounds().contains(mousePos.x, mousePos.y))
            bombBox.setOutlineColor(sf::Color::Cyan);

    
        if (selectedTower == "Cannon")
            cannonBox.setOutlineColor(sf::Color::Yellow);

        if (selectedTower == "Sniper")
            sniperBox.setOutlineColor(sf::Color::Yellow);

        if (selectedTower == "Machine")
            machineBox.setOutlineColor(sf::Color::Yellow);

        if (selectedTower == "Slow")
            slowBox.setOutlineColor(sf::Color::Yellow);

        if (selectedTower == "Bomb")
            bombBox.setOutlineColor(sf::Color::Yellow);
       
        window.draw(cannonBox);
        window.draw(cannonText);
        window.draw(sniperBox);
        window.draw(sniperText);
        window.draw(machineBox);
        window.draw(machineText);
        window.draw(slowBox);
        window.draw(slowText);
        window.draw(bombBox);
        window.draw(bombText);
        window.draw(lifeBox);
        window.draw(smallHeartSprite);
        window.draw(lifeText);
        window.display();
    }
    return 0;
}
