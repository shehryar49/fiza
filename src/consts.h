#ifndef CONSTS_H
#define CONSTS_H

/// install path for windows 32bit
#define INSTALL_DIR_WIN32 "C:\\plutonium\\modules\\"

/// install path for windows 64bit
#define INSTALL_DIR_WIN64 INSTALL_DIR_WIN32

/// install path for linux
#define INSTALL_DIR_LINUX "/opt/plutonium/modules/"

/// repo URL
#define REPO_URL "http://https://plutonium-lang.000webhostapp.com/fiza/"

#ifdef __linux__
#define PLATFORM_STR "Linux"
#else
#define PLATFORM_STR "Windows"
#endif

#endif
