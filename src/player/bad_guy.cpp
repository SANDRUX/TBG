#include <TBG/Player.hpp>
#include <TBG/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "bad_guy.hpp"
#include <iostream>

void * bad_guy(void * arg)
{
    static int b_x = 0, b_y = 0;

    tuxPlayer::Player pos = *static_cast<tuxPlayer::Player *>(arg);


    if (b_x > pos.get_coordinate().x)
    {
        b_x -= 5;
    }

    else if (b_x < pos.get_coordinate().x)
    {
        b_x += 5;
    }

    if (b_y > pos.get_coordinate().y)
    {
        b_y -= 5;
    }

    else if (b_y > pos.get_coordinate().y)
    {
        b_y -= 5;
    }

    tuxPlayer::Player curr;

    tuxPlayer::Position curr_pos {b_x, b_y};

    curr.set_coordinate(curr_pos);

    return &curr;
}