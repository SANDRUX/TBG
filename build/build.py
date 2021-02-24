#!/usr/bin/env python3

import os
from sys import platform

if platform == "linux" or platform == "linux2":

    os.system("./linux_build.sh")    

elif platform == "darwin":

    os.system("./x_build.sh")

os.system('clear')

os.system("./../bin/run")
