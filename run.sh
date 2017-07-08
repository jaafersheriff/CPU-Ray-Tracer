#!/usr/bin/bash

# Pre
clear
rm out*

#Build
echo "Building..."
cd build
cmake ..
make

# If successful compile
if [ $? -eq 0 ]
then
	cd ..
	time ./build/raytrace $@

	# If render flag is set
	if [ "$1" == "render" ]
	then
		cygstart.exe output.png
	fi
else
	cd ..
	echo "FAIL"
fi
