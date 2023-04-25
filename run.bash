#!/bin/bash

g++ main.cpp ./Components/defs/engine.cpp ./Components/defs/Helpers.cpp ./Components/defs/character.cpp ./Components/defs/MapManagement.cpp ./Components/defs/Timer.cpp ./Components/defs/hero.cpp ./Helpers/Colors.cpp ./Components/defs/Field.cpp ./Components/defs/static_objects.cpp -o program.out -w -lSDL2 -lSDL2_image
chmod 777 ./program.out
./program.out