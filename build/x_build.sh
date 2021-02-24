#!/bin/bash

export TBG_INCLUDE=$HOME/TBG/include
export TBG_SRC=$HOME/TBG/src

brew install sfml

[ -f /usr/bin/g++ ] && echo g++ is already installed || brew install g++
g++ $TBG_SRC/Player/Player.cpp $TBG_SRC/Network/Network.cpp $TBG_SRC/System/System.cpp -o ../bin/run -I $TBG_INCLUDE/. -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -pthread