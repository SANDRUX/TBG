#include <TBG/Exception.hpp>
#include <cstdio>
#include "frames.hpp"

void display_frame(const int mode)
{
    switch (mode)
    {
        case int(move::UP):
            //TODO
            break;

        case int(move::DOWN):
            //TODO
            break;

        case int(move::RIGHT):
            //TODO
            break;

        case int(move::LEFT):
            //TODO
            break;

        default:
            throw tuxException::TuxException("Incorrect mode passed!");
    }
}