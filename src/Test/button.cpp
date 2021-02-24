#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <unistd.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(),"Test Button", sf::Style::Default);
    
    sf::RectangleShape shape(sf::Vector2f(50.f, 50.f));

    sf::Vector2f pos(0.f, 0.f);

    shape.setFillColor (sf::Color::Red);
    shape.setPosition(pos);

    while (window.isOpen())
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {   
                std::cout << "Button is pressed!" << std::endl;
                sf::Vector2i mpos = sf::Mouse::getPosition(window);

                if (mpos.x >= 0 && mpos.x <= 50 && mpos.x >= 0 && mpos.y <= 50)
                {
                    std::cout << mpos.x << " " << mpos.y << std::endl;
                    shape.setFillColor(sf::Color::Green);
                }                
            } 
        }

        window.clear(sf::Color::Cyan);

        window.draw(shape);

        // std::cout << "Something" << std::endl;

        window.display();
    }
    

    return 0;
}