#!/bin/bash

export TBG_DEPEND=$HOME/TBG/libs

    unameOut="$(uname -s)"

    if [[ $(unameOut) -eq Linux ]]
    then
        wget https://www.sfml-dev.org/files/SFML-2.5.1-linux-gcc-64-bit.tar.gz -P $TBG_DEPEND

    elif [[ $(unameOut) -eq Darwin ]]
    then 
        wget https://www.sfml-dev.org/files/SFML-2.5.1-macOS-clang.tar.gz $TBG_DEPEND
    fi
        
    cd $TBG_DEPEND

    gunzip SFML-2.5.1-linux-gcc-64-bit.tar.gz
    tar -xf SFML-2.5.1-linux-gcc-64-bit.tar

    rm -rf SFML-2.5.1-linux-gcc-64-bit.tar




