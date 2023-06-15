#!/bin/bash
if [ $# = 0 ]; then
	echo "building release config";
	g++ src/*.h src/*.cpp -o fiza;
elif [ $1 = "debug" ]; then
	echo "building debug config";
	g++ src/*.h src/*.cpp -g -o fiza;
fi
