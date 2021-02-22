#pragma once

#include <string>

namespace tuxPlayer
{
    struct Position
    {
        int x;
        int y;
    };

    class Player
    {
    public:
        inline void set_coordinate(const Position & coordinate) { this->m_coordinate = coordinate; }
        inline const Position &get_coordinate(void) const { return this->m_coordinate; }
        inline void set_name(const std::string & name) { this->m_name = name; }
        inline const std::string &get_name(void) const { return this->m_name; }

    private:
        std::string m_name;
        Position m_coordinate;
    };
};
