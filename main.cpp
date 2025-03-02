#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <vector>

const sf::Color background_color = sf::Color::White;
const sf::Color line_color = sf::Color::Black;
const float screen_width = 900.0f;
const float screen_height = 900.0f;

class Game;

void draw_lines(sf::RenderWindow& window)
{
    for (int i = 0; i<4; i++)
    {
        sf::RectangleShape rectangle;
        rectangle.setFillColor(line_color);
        rectangle.setSize({10, 610});
        rectangle.setPosition(200.0f + 200.0f * i, 200.0f);
        window.draw(rectangle);
    }
    for (int i = 0; i<4; i++)
    {
        sf::RectangleShape rectangle;
        rectangle.setFillColor(line_color);
        rectangle.setSize({600, 10});
        rectangle.setPosition(200.0f, 200.0f + 200.0f * i);
        window.draw(rectangle);
    }
}

class Game
{
    public:
    Game();
    void run();

    private:
    sf::RenderWindow window;
    sf::Sprite cross, circle;
    sf::Sprite temp_cross, temp_circle;
    sf::Texture texture_cross, texture_circle;
    std::vector <sf::Sprite> marks;
    int index = 0;

    private:
    void render();
    void process_events();
    void handle_input(sf::Event event, int index);

};

Game::Game():window(sf::VideoMode(screen_width, screen_height), "TicTacToe")
{
    if (!texture_cross.loadFromFile("assets/cross.png"))
    {
        std::cout << "Error in loading cross" << std::endl; 

    }
    cross.setTexture(texture_cross);
    cross.setPosition(screen_width/2 - 100.0f, screen_height/2);
    
    if (!texture_circle.loadFromFile("assets/circle.png"))
    {
        std::cout << "Error in loading circle" << std::endl;
    }
    circle.setTexture(texture_circle);
    circle.setPosition(screen_width/2 + 100.0f, screen_height/2);
    temp_cross = cross;
    temp_circle = circle;
}

void Game::render()
{

    window.clear(background_color);
    draw_lines(window);
    for (auto& units : marks)
    {
        window.draw(units);
    }
    window.display();
}

void Game::process_events()
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::MouseButtonPressed:
                handle_input(event, index);
                index++;
                break;
            case sf::Event::Closed:
                window.close();
                break;
        }
    }
}


void Game::handle_input(sf::Event event, int index)
{
    float click_x = event.mouseButton.x;
    float click_y = event.mouseButton.y;

    // Ensure the click is inside the grid (200,200) to (800,800)
    if (click_x < 200 || click_x > 800 || click_y < 200 || click_y > 800)
        return;

    // Compute row and column
    int col = (click_x - 200) / 200;
    int row = (click_y - 200) / 200;

    std::cout << "Clicked on cell (" << row << ", " << col << ")" << std::endl;

    // Set the symbol position based on the computed cell
    if (index % 2 == 0)
    {
        temp_cross.setPosition(col * 200 + 200 + 50, row * 200 + 200 + 50);
        marks.push_back(temp_cross);
        
    }
    else
    {
        temp_circle.setPosition(col * 200 + 200 + 50, row * 200 + 200 + 50);
        marks.push_back(temp_circle);
    }

}

void Game::run()
{
    while(window.isOpen())
    {
        process_events();
        render();
    }
}

int main()
{
    Game game;
    game.run();
}
