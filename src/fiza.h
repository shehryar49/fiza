#ifndef FIZA_H
#define FIZA_H
#include <string>
#include <vector>

/// Installs `packageName`.
/// use quiet flag to control whether to output to stdout/err or not.
///
/// Returns: true if done, false if errored
bool packageInstall(std::string packageName, bool quiet = false);

/// Removes `packageName`.
/// use quiet flag to control whether to output to stdout/err or not.
///
/// Returns: true if done, false if errored
bool packageRemove(std::string packageName, bool quiet = false);

/// Finds all packages installed.
///
/// Returns: std::vector<std::string>, names of all packages installed
std::vector<std::string> packageListInstalled();

/// Checks if a package is installed.
///
/// Returns: true if package is installed
bool packageIsInstalled(std::string packageName);

/// Fetches list of all packages from repo
///
/// Returns: names of all packages in repo
std::vector<std::string> packageListAvailable();

/// Checks if a package exists on repo
///
/// Returns: true if package exists on repo
bool packageIsAvailable(std::string packageName);

#endif
