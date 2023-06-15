#include <iostream>
#include <string>
#include <string.h>

#include "consts.h"

const char* USAGE_STR =
	"Fiza - package manager for Plutonium - " PLATFORM_STR "\n"
	"Usage:"
	"\tfiza <command> <package>\n"
	"\tvalid commands are:\n"
	"\tinstall\t\tInstall a package\n"
	"\tremove\t\tRemove a package\n";

int main(int argc, char** argv){
	if (argc < 3){
		std::cerr << USAGE_STR;
		exit(1);
	}
	if (strcmp("install", argv[1])){
		// TODO continue from here
	}
}
