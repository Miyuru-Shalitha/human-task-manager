#!/bin/bash

if [ ! -d "build" ]; then
    mkdir build
fi

command="gcc -std=c23 -g ../source/main.c -o human-task-manager"

cd build
bear -- $command
$command
cd ..
