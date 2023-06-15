#ifndef CONSTS_H
#define CONSTS_H

/// repo URL
#define REPO_URL "http://https://plutonium-lang.000webhostapp.com/fiza/"

#ifdef __linux__
#define PLATFORM_STR "Linux"
#define INSTALL_DIR "/opt/plutonium/modules/"
#define PKG_EXT ".so"
#elif _WIN32 || _WIN64
#define PLATFORM_STR "Windows"
#define INSTALL_DIR "C:\\plutonium\\modules\\"
#define PKG_EXT ".dll"
#endif

#endif
