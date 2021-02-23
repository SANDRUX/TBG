#include <TBG/Player.hpp>
#include <TBG/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "TBG", sf::Style::Default);

    sf::Texture sprite;

    if (!sprite.loadFromFile("../design/WARRIORTUX.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 0;
    }
    
    sf::Sprite shape;
    shape.setTexture(sprite);

    sf::Texture bT;

    if (!bT.loadFromFile("../design/button.png", sf::IntRect(0, 0, 50, 50)))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 0;
    }

    sf::Sprite button;
    button.setTexture(bT);

    sf::Vector2f button_position(910.f, 490.f);
    button.setPosition(button_position);

    tuxPlayer::Position pos{0, 0};
    tuxPlayer::Player player;

    player.set_name("Player");
    player.set_coordinate(pos);

    sf::SoundBuffer sBuffer;

    if (!sBuffer.loadFromFile("../audio/steps.wav"))
    {
        std::cerr << "Error occurred when loading sound buffer from a file!";
        exit(EXIT_FAILURE);
    }

    sf::Sound sound;
    sound.setBuffer(sBuffer);

    bool status = false;

    window.clear(sf::Color::White);
    window.draw(button);
    window.display();
    
    // run the program as long as the window is open

    while (true)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i mpos = sf::Mouse::getPosition(window);

            if (mpos.x >= 910 && mpos.x <= 960 && mpos.x >= 490 && mpos.y <= 540)
            {
                std::cout << mpos.x << " " << mpos.y << std::endl;
                break;
            }
        }
    }

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
                    sound.play();
                }

                else if(event.key.code == sf::Keyboard::Right)
                {
                    pos = player.get_coordinate();
                    pos.x += 50;
                    player.set_coordinate(pos);
                    sound.play();
                }

                else if(event.key.code == sf::Keyboard::Down)
                {
                    pos = player.get_coordinate();
                    pos.y += 50;
                    player.set_coordinate(pos);
                    sound.play();
                }

                else if (event.key.code == sf::Keyboard::Up)
                {
                    pos = player.get_coordinate();
                    pos.y -= 50;
                    player.set_coordinate(pos);
                    sound.play();
                }     
            }
        }

        window.clear(sf::Color::White);

        shape.setPosition(pos.x, pos.y);

        window.draw(shape);

        window.display();
    }

    return 0;
}