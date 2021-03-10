#include <TBG/Exception.hpp>
#include <cstdio>
#include "frames.hpp"

void display_frame(const int mode, const std::string & conf)
{
    switch (mode)
    {
        case static_cast<int>(move::UP):
            //TODO
            break;

        case static_cast<int>(move::DOWN):
            //TODO
            break;

        case static_cast<int>(move::RIGHT):
            //TODO
            break;

        case static_cast<int>(move::LEFT):
            //TODO
            break;

        default:
            throw tuxException::TuxException("Incorrect mode passed!");
    }
}