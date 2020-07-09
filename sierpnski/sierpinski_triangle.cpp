#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<random>
#include<vector>

const float SCREEN_HEIGHT = 600.f;
const float SCREEN_WIDTH= 600.f;
const std::vector<sf::Vector2f> vertices{ sf::Vector2f(300.f, 0.f), sf::Vector2f(0.f, 600.f), sf::Vector2f(600.f, 600.f) };
// const sf::Vector2f v_1(5.f, 598.f);  //initial point inside triangle 

static std::random_device rd;
static std::mt19937 generator(rd());

sf::Color color(sf::Color::Cyan);

sf::Vector2f get_next_point(sf::Vector2f v)
{
	std::uniform_int_distribution<int> distribution(0, 2);
    int random_number = distribution(generator);

    if(random_number == 0) color = sf::Color::Red;
    if(random_number == 1) color = sf::Color::Cyan;
    if(random_number == 2) color = sf::Color::Yellow;

    float v_new_x = 0.5 * (v.x + vertices[random_number].x);
    float v_new_y = 0.5 * (v.y + vertices[random_number].y);

    return sf::Vector2f(v_new_x, v_new_y);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Sierpinski Triangle", sf::Style::Default);
	window.setPosition(sf::Vector2i(700, 50));
	sf::Vector2f position(5.f, 598.f);
	window.clear();

	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		}

		sf::CircleShape point(0.2);
		point.setPosition(position);
		point.setFillColor(color);
		window.draw(point);
		window.display();
		position = get_next_point(position);
	}
}