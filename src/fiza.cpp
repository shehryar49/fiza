#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

#include "consts.h"
#include "fiza.h"

/// Gets URLs to fetch for a packageName
///
/// Returns: URL
std::string packageUrl(std::string packageName){
#ifdef __linux__
	return REPO_URL + packageName + "/source.zip";
#elif _WIN32
	return REPO_URL + packageName + "/win32.zip";
#elif _WIN64
	return REPO_URL + packageName + "/win64.zip";
#else
	return null;
#endif
}

/// Checks if a string ends with another string
///
/// Returns: true if matches
bool hasEnding(const std::string &str, const std::string &end) {
	if (str.length() < end.length())
		return false;
	return str.compare(str.length() - end.length(), end.length(), end) == 0;;
}

bool packageInstall(std::string packageName, bool quiet){
	if (!quiet){
		std::cout << "Installing package " << packageName << "\n";
	}

	bool status = false;
	auto url = packageUrl(packageName);
	try{
#ifdef __linux__
		// TODO run `sh | curl "url+/build.sh`
#else
		// extract `packageURL()` into INSTALL_DIR
#endif
	}catch (...){
		if (!quiet){
			std::cerr << "Installation failed\n";
		}
		return false;
	}
	return true;
}

bool packageRemove(std::string packageName, bool quiet){
	if (std::remove((INSTALL_DIR + packageName + PKG_EXT).c_str())){
		return true;
	}
	if (!quiet){
		std::cerr << "Failed to remove file " + packageName + PKG_EXT + "\n";
	}
	return false;
}

std::vector<std::string> packageListInstalled(){
	std::vector<std::string> ret;
	for (const auto &entry : std::filesystem::directory_iterator(INSTALL_DIR)){
		std::string name = entry.path().filename();
		if (!hasEnding(name, PKG_EXT))
			continue; // not a dll or so file, skip it
		ret.push_back(name);
	}
	return ret;
}

bool packageIsInstalled(std::string packageName){
	std::string match = packageName + PKG_EXT;
	for (const auto &entry : std::filesystem::directory_iterator(INSTALL_DIR)){
		std::string name = entry.path().filename();
		if (entry.path().filename() == match)
			return true;
	}
	return false;
}
