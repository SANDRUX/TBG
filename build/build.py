#!/usr/bin/env python3

import os
from sys import platform

if platform == "linux" or platform == "linux2":

    os.system("sudo apt-get update")
    os.system("sudo apt-get install libsfml-dev")
    os.system("[ -f /usr/bin/g++ ] && echo g++ is already installed || sudo apt install -y g++")
    os.system("g++ ../src/tbg_main_player.cpp ../src/tbg_network.cpp -o ../bin/run -I ../include -lsfml-graphics -lsfml-window -lsfml-system")

elif platform == "darwin":

    os.system("brew install sfml")
    os.system("[ -f /usr/bin/g++ ] && echo g++ is already installed || brew install g++")
    os.system("g++ -std=c++11 ../src/tbg_main_player.cpp  -o ../bin/run -I ../include -lsfml-graphics -lsfml-window -lsfml-system")

os.system('clear')

os.system("./../bin/run")
