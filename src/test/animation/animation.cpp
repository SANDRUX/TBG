// Demonstrate creating a spritesheet
#include "SFML/Graphics.hpp"
int main(int argc, char **argv)
{
    sf::RenderWindow renderWindow(sf::VideoMode(640, 480), "Demo Game");
    sf::Event event;
    sf::Texture texture;
    texture.loadFromFile("[pathname to animations file]");
    sf::IntRect rectSourceSprite(300, 0, 300, 400);
    sf::Sprite sprite(texture, rectSourceSprite);
    sf::Clock clock;
    while (renderWindow.isOpen())
    {
        while (renderWindow.pollEvent(event))
        {
            if (event.type == sf::Event::EventType::Closed)
                renderWindow.close();
        }
        if (clock.getElapsedTime().asSeconds() > 1.0f)
        {
            if (rectSourceSprite.left == 600)
                rectSourceSprite.left = 0;
            else
                rectSourceSprite.left += 300;
            sprite.setTextureRect(rectSourceSprite);
            clock.restart();
        }

        renderWindow.clear();
        renderWindow.draw(sprite);
        renderWindow.display();
    }
}