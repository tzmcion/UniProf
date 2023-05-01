#!/bin/bash

g++ main.cpp ./Components/defs/engine.cpp \
 ./Components/defs/Helpers.cpp \
 ./Components/defs/character.cpp \
 ./Components/defs/MapManagement.cpp \
 ./Components/defs/Timer.cpp \
 ./Components/defs/hero.cpp \
 ./Helpers/Colors.cpp \
 ./Components/defs/Field.cpp \
 ./Components/defs/static_objects.cpp \
 ./Components/defs/Input_Manager.cpp \
 ./Components/defs/messenger.cpp \
 ./Levels/defs/Level1.cpp \
 ./Levels/defs/Base_Level.cpp \
 ./Components/defs/Buttons.cpp \
 ./Components/defs/Board.cpp \
 ./Helpers/Texture_Loader.cpp \
 -o program.out -w -lSDL2 -lSDL2_image -lSDL2_ttf
chmod 777 ./program.out
./program.out