#include <tbg_player.hpp>
#include <tbg_network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Client", sf::Style::Fullscreen);

    sf::Texture sprite;

    if (!sprite.loadFromFile("../design/WARRIORTUX.png"))
    {
        std::cout << "Could not load texture" << std::endl;
        return 0;
    }
    
    sf::Sprite shape;
    shape.setTexture(sprite);
    
    player::Position pos{0, 0};

    player::Player player;

    player.set_name("Player");
    player.set_coordinate(pos);




    // run the program as long as the window is open
    while (window.isOpen())
    {
        

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
                    pos = player.get_coordinate();
                    pos.x -= 50;
                    player.set_coordinate(pos);   
                }

                else if(event.key.code == sf::Keyboard::Right)
                {
                    pos = player.get_coordinate();
                    pos.x += 50;
                    player.set_coordinate(pos);
                }

                else if(event.key.code == sf::Keyboard::Down)
                {
                    pos = player.get_coordinate();
                    pos.y += 50;
                    player.set_coordinate(pos);
                }

                else if (event.key.code == sf::Keyboard::Up)
                {
                    pos = player.get_coordinate();
                    pos.y -= 50;
                    player.set_coordinate(pos);
                }
            }
                
        }



        // clear the window with black color // /home/sandro/MEMES/MANUX.jpg
        window.clear(sf::Color::White);

        shape.setPosition(pos.x, pos.y);
        window.draw(shape);

        window.display();
        // }
        
    }

    return 0;
}