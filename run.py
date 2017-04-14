#!/usr/bin/env python
import subprocess
import sys
import commands

def runLine(command):
    return subprocess.call(command, shell=True)

runLine("clear")
runLine("echo -n Compiling...")
if (runLine("g++ src/*.cpp -I/cygdrive/c/Users/jaafe/Documents/Code/libs/glm-0.9.8.4/ -o build/raytrace > compileOut")) == 0:
    runLine("echo done")
    args = "";
    for i in range (1, len(sys.argv)):
        args += sys.argv[i] + " ";
    runLine("./build/raytrace " + args);
    if (sys.argv[1] == "render"):
        runLine("cygstart.exe output.png");
else:
    runLine("echo ERROR!");
    runLine("cat compileOut");
runLine("rm compileOut");
