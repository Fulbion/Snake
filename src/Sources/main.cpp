#include <SFML/Graphics.hpp>
#include <time.h>
#include <Windows.h>

const unsigned int size = 20;
const int width = 4 * size * 10;
const int height = 3 * size * 10;
const char* title = "Snake";
sf::Vector2f pos(sf::Vector2f(width / 2, height / 2));
sf::Vector2f fpos(sf::Vector2f((rand() % (width / size)) * size, (rand() % (height / size)) * size));

int score = 0;

enum class Direction
{
    Stop,
    Left,
    Down,
    Up,
    Right
};
auto direction = Direction::Stop;

struct Snake { sf::Vector2f pos; } s[255];
int length = 1;

void Move(sf::Sprite& snake)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  {  if (direction != Direction::Right) direction = Direction::Left; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  {     if (direction != Direction::Up) direction = Direction::Down; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    {     if (direction != Direction::Down) direction = Direction::Up; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {  if (direction != Direction::Left) direction = Direction::Right; }

    if (direction == Direction::Left) s[0].pos.x -= size;
    if (direction == Direction::Down) s[0].pos.y += size;
    if (direction == Direction::Up)   s[0].pos.y -= size;
    if (direction == Direction::Right)s[0].pos.x += size;
    if (direction == Direction::Stop) snake.move(0, 0);

    for (int i = length; i > 0; --i)
    {
        s[i].pos.x = s[i - 1].pos.x;
        s[i].pos.y = s[i - 1].pos.y;
    }
}


bool Eat(sf::Sprite& food)
{
    return s[0].pos == food.getPosition();
}

void GameOver()
{
    s[0].pos = sf::Vector2f(width / 2, height / 2);
    //fpos = sf::Vector2f((rand() % (width / size)) * size, (rand() % (height / size)) * size);
    direction = Direction::Stop;
    length = 1;
}

int main()
{
    srand(time(NULL));
    ShowWindow(GetConsoleWindow(), 0);

    sf::RenderWindow window(sf::VideoMode(width, height), title, sf::Style::Close);

    sf::Texture texture1, texture2;
    texture1.loadFromFile("images/block.bmp");
    texture2.loadFromFile("images/grid.bmp");

    sf::Sprite snake(texture1);
    sf::Sprite body(texture1);
    sf::Sprite food(texture1);
    sf::Sprite grid(texture2);

    float tick = 0.5f;
    s[0].pos = pos;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        if (tick < 0.5f) tick = 0.5f;
        window.setFramerateLimit(tick * 24);
        window.draw(grid);

        Move(snake);
        if (Eat(snake, food))
        {
            fpos = sf::Vector2f((rand() % (width / size)) * size, (rand() % (height / size)) * size);
            tick += 0.01f;
            score += 10;
            length++;
        }

        for (int i = 0; i < length; i++)
        {
            if (s[0].pos == s[i+2].pos)
            {
                if (direction != Direction::Stop)
                {
                    tick = 0.0416667f;
                    GameOver();
                }
            }
            else if (s[0].pos.x < 0 || s[0].pos.x >= width || s[0].pos.y < 0 || s[0].pos.y >= height)
            {
                tick = 0.0416667f;
                GameOver();
            }
        }

        
        for (int i = 0; i <= length; i++) { snake.setPosition(s[i].pos); window.draw(snake); }
        food.setPosition(fpos); window.draw(food);

        window.display();
    }

    return 0;
}
