#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<random>

//lot of info used from https://en.wikipedia.org/wiki/Barnsley_fern

const double WINDOW_HEIGHT = 600.f;
const double WINDOW_WIDTH = 600.f;
const double X_SCALING_FACTOR = (WINDOW_WIDTH/4.8478);
const double Y_SCALING_FACTOR = (WINDOW_HEIGHT/9.9983);

static std::random_device rd;
static std::mt19937 generator(rd());

sf::Vector2f next_point(sf::Vector2f previous_point)
{
    std::uniform_real_distribution<double> distribution(0, 1);
    double random_number = distribution(generator);
    
    float x = previous_point.x;
    float y = previous_point.y;
    
    if(random_number <= 0.01)
    {
        float x_next = 0.0f;
        float y_next = 0.16*y;
        return sf::Vector2f(x_next, y_next);
    }
    else if(random_number <= 0.86)
    {
        float x_next = 0.85*x + 0.04*y;
        float y_next = -0.04*x + 0.85*y + 1.6;
        return sf::Vector2f(x_next, y_next);
    }
    else if(random_number <= 0.93)
    {
        float x_next = 0.2*x - 0.26*y;
        float y_next = 0.23*x + 0.22*y + 1.6;
        return sf::Vector2f(x_next, y_next);
    }
    else
    {
        float x_next = -0.15*x + 0.28*y;
        float y_next = 0.26*x + 0.24*y + 0.44;
        return sf::Vector2f(x_next, y_next);
    }
}


int main()
{

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Barnsley Fern", sf::Style::Default);
    sf::Vector2f position(0.f, 0.f);
    window.clear(sf::Color::Black);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        sf::CircleShape point(0.4);
        std::uniform_real_distribution<double> distribution(0, 1);
        if(distribution(generator) <= 0.5)
            point.setFillColor(sf::Color::Cyan);
        else 
            point.setFillColor(sf::Color::White);
        point.setPosition((position.x + 2.1820) * X_SCALING_FACTOR, (position.y * Y_SCALING_FACTOR));
        window.draw(point);
        window.display();
        position = next_point(position);
    }

    return 0;
}
