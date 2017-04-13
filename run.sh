#!/bin/bash

if g++ src/*.cpp -I/cygdrive/c/Users/jaafe/Documents/Code/libs/glm-0.9.8.4/ -o build/raytrace
then
   ./build/raytrace $@
else
   echo "Failed compiliation"
fi
