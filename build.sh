#!/bin/bash
if [ $# = 0 ]; then
	echo "building release config";
	g++ src/*.h src/*.cpp -s -O3 -o fiza -lcurl;
elif [ $1 = "debug" ]; then
	echo "building debug config";
	g++ src/*.h src/*.cpp -g -o fiza -lcurl;
fi
