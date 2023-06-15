#include <iostream>
#include <string>
#include <string.h>

#include "consts.h"
#include "validate.h"

const char* USAGE_STR =
	"Fiza - package manager for Plutonium - " PLATFORM_STR "\n"
	"Usage:"
	"\tfiza <command> <package>\n"
	"\tvalid commands are:\n"
	"\tinstall\t\tInstall a package\n"
	"\tremove\t\tRemove a package\n";

int main(int argc, char** argv){
	if (argc != 3){
		std::cerr << USAGE_STR;
		exit(1);
	}
	std::string packageName = argv[2],
		command = argv[1];

	if (!packageNameIsValid(packageName)){
		std::cerr << "Package name seems to be invalid.\n";
		exit(1);
	}

	if (command == "install"){
		// TODO install

	}else if (command == "remove"){
		// TODO remove

	}else{
		std::cerr << USAGE_STR;
		exit(1);
	}
	return 0;
}
