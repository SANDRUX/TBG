#!/usr/bin/env python3

import os

home = os.getenv('HOME')

with open(home + '/TBG/bin/TBG.desktop', 'r+') as f:
    string = f.read()
    f.seek(0)

    string = string.replace('[home]', home)    

    f.write(string)

