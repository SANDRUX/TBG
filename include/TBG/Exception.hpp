#pragma once

#include <iostream>
#include <exception>

namespace tuxException
{
    class TuxException : public std::exception
    {
    public:

        TuxException(std::string error) : m_error{error}
        {

        }
        
        const char *what() const noexcept override { return m_error.c_str(); }
    
    private:

        std::string m_error{};
        
    };
}
