#include <SFML/Graphics.hpp>
#include <iostream>

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
                // sf::Vector2i micePos = sf::Mouse::getPosition();

                // if (micePos.x >= float(0) && micePos.x < float(50) && micePos.y >= float(0) && micePos.y < float(50))
                // {
                //     std::cout << "Button is pressed!" << std::endl;
                //     std::cout << micePos.x << " " << micePos.y << std::endl;
                // }                
            } 
        }

        window.clear(sf::Color::Cyan);

        window.draw(shape);

        // std::cout << "Something" << std::endl;

        window.display();
    }
    

    return 0;
}