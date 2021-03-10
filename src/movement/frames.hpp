#pragma once

#include <TBG/Exception.hpp>
#include <string>

enum class move
{
    UP,
    DOWN,
    RIGHT,
    LEFT    
};

void display_frame(const int, const std::string &);