#include <TBG/Player.hpp>
#include <TBG/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "bad_guy.hpp"
#include <iostream>

extern tuxPlayer::Player player;
extern tuxPlayer::Position pos;

extern tuxPlayer::Player *bGuy;
extern tuxPlayer::Position bPos;

void * bad_guy(void * arg)
{
    if (bGuy->get_coordinate().x > player.get_coordinate().x)
    {
        bPos.x -= 10;
        bGuy->set_coordinate(bPos);
    }

    else if (bGuy->get_coordinate().x < player.get_coordinate().x)
    {
        bPos.x += 10;
        bGuy->set_coordinate(bPos);
    }

    if (bGuy->get_coordinate().y > player.get_coordinate().y)
    {
        bPos.y -= 10;
        bGuy->set_coordinate(bPos);
    }

    else if (bGuy->get_coordinate().y < player.get_coordinate().y)
    {
        bPos.y += 10;
        bGuy->set_coordinate(bPos);
    }

    return static_cast<void *>(nullptr);
}