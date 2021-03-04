#include <TBG/Player.hpp>
#include <TBG/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "OBJ/bad_guy.hpp"
#include <iostream>

void * bad_guy(void * pos)
{
    int b_x, b_y;

    tuxPlayer::Player pos = *reinterpret_cast<tuxPlayer::Player *>(pos);
}