# HTTP Packages Repository Structure

## `/fiza/packages.txt`

A newline (`\n`) separated list of names of all packages available

## `/fiza/package/:PACKAGE_NAME/win32.zip`

32 bit windows DLLs for a package

## `/fiza/package/:PACKAGE_NAME/win64.zip`

64 bit windows DLLs for a package

## `/fiza/package/:PACKAGE_NAME/source.zip`

Source files for a package

## `/fiza/package/:PACKAGE_NAME/build.sh`

Linux shell script to build the package
