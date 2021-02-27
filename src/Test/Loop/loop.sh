#!/bin/bash

export TBG_INCLUDE=$HOME/TBG/include
export TBG_SRC=$HOME/TBG/src

g++ client.cpp $TBG_SRC/Network/Network.cpp $TBG_SRC/System/System.cpp -o client.exe -I $TBG_INCLUDE/. -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -pthread
g++ server.cpp $TBG_SRC/Network/Network.cpp $TBG_SRC/System/System.cpp -o server.exe -I $TBG_INCLUDE/. -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -pthread
