#include <TBG/Player.hpp>
#include <TBG/Network.hpp>
#include <TBG/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "bad_guy.hpp"

tuxSystem::TuxMutex mtx;

tuxPlayer::Player player;
tuxPlayer::Position pos{0, 0};

tuxPlayer::Player * bGuy = new tuxPlayer::Player;
tuxPlayer::Position bPos{1000, 1000};

void * thread_func(void * arg)
{
    try
   {
        while(true)
        {
            do
            {
                mtx.lock();

                bad_guy(static_cast<void *>(&player));

                mtx.unlock();

                usleep(200000);

            } while (bGuy->get_coordinate().x != player.get_coordinate().x && bGuy->get_coordinate().y != player.get_coordinate().y);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return nullptr;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "TBG", sf::Style::Default);

    std::cout << sf::VideoMode::getDesktopMode().height << " " << sf::VideoMode::getDesktopMode().width;
    window.setFramerateLimit(20);
    sf::Texture sprite;

    if (!sprite.loadFromFile("../design/WARRIORTUX.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 0;
    }
    
    sf::Sprite shape;
    shape.setTexture(sprite);

    sf::Texture bT;

    if (!bT.loadFromFile("../design/button.png", sf::IntRect(0, 0, 200, 80)))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 0;
    }

    sf::Sprite button;
    button.setTexture(bT);

    sf::Vector2f button_position(760.f, 460.f);
    button.setPosition(button_position);

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

    sf::Music intro;

    if(!intro.openFromFile("../audio/beeh.wav"))
    {
        std::cerr << "Error caught when loading the musick from a file!";
        return -1;
    }

    intro.play();

    bool status = false;

    window.clear(sf::Color::White);
    window.draw(button);
    window.display();
    
    // run the program as long as the window is open

    tuxSystem::TuxThread bad_guy(thread_func);

    bGuy = new tuxPlayer::Player;

    bGuy->set_coordinate(bPos);

    sf::CircleShape b_shape(50.f);

    b_shape.setFillColor(sf::Color(0xFF, 0, 0));

    sf::Vector2f temp(bGuy->get_coordinate().x, bGuy->get_coordinate().y);

    b_shape.setPosition(temp);

    while (true)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i mpos = sf::Mouse::getPosition(window);

            if (mpos.x >= 760 && mpos.x <= 960 && mpos.x >= 480 && mpos.y <= 540)
            {
                std::cout << mpos.x << " " << mpos.y << std::endl;
                intro.stop();
                break;
            }
        }
    }

    pthread_t tid;

    bad_guy.launch(tid, nullptr);

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
                mtx.lock();

                if (event.key.code == sf::Keyboard::Left)
                {
                    pos = player.get_coordinate();
                    pos.x -= 50;
                    player.set_coordinate(pos);
                    sound.play();
                }

                else if (event.key.code == sf::Keyboard::Right)
                {
                    pos = player.get_coordinate();
                    pos.x += 50;
                    player.set_coordinate(pos);
                    sound.play();
                }

                else if (event.key.code == sf::Keyboard::Down)
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

                mtx.unlock();
            }
        }

        window.clear(sf::Color::White);

        std::cout << pos.x << " " << pos.y << std::endl;
        
        pos = player.get_coordinate();

        shape.setPosition(pos.x, pos.y);
        b_shape.setPosition(bGuy->get_coordinate().x, bGuy->get_coordinate().y);
        
        window.draw(shape);
        window.draw(b_shape);

        window.display();
    }

    return 0;
}