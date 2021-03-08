#!/bin/bash

export TBG_INCLUDE=$HOME/TBG/include
export TBG_SRC=$HOME/TBG/src
export TBG_DEPEND=$HOME/TBG/libs/SFML-2.5.1

    unameOut="$(uname -s)"

    if [[ ${unameOut} -eq Linux ]]
    then
        which apt || (echo "apt not installed" && exit)
        [ -f /usr/bin/g++ ] && echo g++ is already installed || sudo apt install -y g++
    
    elif [[ ${unameOut} -eq Darwin ]]
    then
        [ -f /usr/bin/g++ ] && echo g++ is already installed || brew install g++
    fi

    g++ $TBG_SRC/player/player.cpp $TBG_SRC/player/bad_guy.cpp $TBG_SRC/network/network.cpp $TBG_SRC/system/loop.cpp $TBG_SRC/system/thread.cpp -o ../bin/run -I $TBG_INCLUDE/. -I $TBG_DEPEND/include/. -L $TBG_DEPEND/lib/. -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -pthread

    # -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio