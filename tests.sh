#!/bin/bash

if g++ src/*.cpp -I/cygdrive/c/Users/jaafe/Documents/Code/libs/glm-0.9.8.4/ -o build/raytrace
then
	for i in {1..15}
	do
		echo "Testing $i..."
   	./build/raytrace $(< tests/test$i.args) > mytest$i.out
		if diff mytest$i.out tests/test$i.out > err
		then
			echo "Passed test $i"
		else
			echo "Failed test $i"
			cat err
		rm mytest$i.out
		rm err
		fi
	done
else
   echo "Failed compiliation"
fi
