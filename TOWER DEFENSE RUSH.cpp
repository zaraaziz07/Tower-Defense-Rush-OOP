#include"Entity.h"
#include"Enemy.h"
#include"Tower.h"
#include"Globals.h"


WayPoint waypoints[wayPointsCount] =
{
    { 0 * 32 + 16, 6.5f * 32 },   // (6,7)

    { 7.5f * 32, 6.5f * 32 },     // (7,8) ← FIXED (was 8.5)

    { 7.5f * 32, 17.5f * 32 },    // vertical continues

    { 15.5f * 32, 17.5f * 32 },   // (15,16)

    { 15.5f * 32, 9.5f * 32 },    // (9,10)

    { 25.5f * 32, 9.5f * 32 },    // (25,26)

    { 25.5f * 32, 19.5f * 32 },   // (18,19)

    { 34 * 32 + 16, 19.5f * 32 }  // final horizontal
};
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
int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Tower Defense Rush", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    SetAttackPath();
    SetFences();

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

    BasicEnemy enemy(waypoints,wayPointsCount);
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
        enemy.update();
        enemy.render(window);
        window.display();
    }
    return 0;
}
