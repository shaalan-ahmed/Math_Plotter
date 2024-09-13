#!/bin/bash

clear

compiler=g++

main=../Main/main.cpp

executable=main

$compiler $main -o $executable -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

./$executable