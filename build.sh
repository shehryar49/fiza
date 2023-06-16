#!/bin/bash
if [ $# = 0 ]; then
	echo "building release config";
	g++ src/*.h src/*.cpp -s -O3 -o fiza -lcurl -std=c++17;
elif [ $1 = "debug" ]; then
	echo "building debug config";
	g++ -DDEBUG src/*.h src/*.cpp -g -o fiza -lcurl -std=c++17;
fi
