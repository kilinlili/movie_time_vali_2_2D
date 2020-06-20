#!/bin/bash -x

g++ mov2img.cpp `pkg-config --libs --cflags opencv`
