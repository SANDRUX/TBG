#!/bin/bash

export TBG_INCLUDE=$HOME/TBG/iclude
export TBG_SRC=$HOME/TBG/SRC

sudo apt update

sudo apt-get install libsfml-dev

[ -f /usr/bin/g++ ] && echo g++ is already installed || sudo apt install -y g++
g++ $TBG_SRC/Player/Player.cpp $TBG_SRC/Network/Network.cpp TBG_SRC/System/System.cpp -o ../bin/run -I $TBG_INCLUDE -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -pthread