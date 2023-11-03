# fiza
A simple package manager for [plutonium programming language](https://github.com/shehryar49/plutonium-lang)
Fiza allows you to install plutonium modules(native modules) on all supported platforms conveniently. It does so by downloading plutonium modules from github repos. Every module has it's own repo. On Windows, it downloads module binaries(dll files) and places them in C:\plutonium\modules . On Unix like systems (Linux and Mac OS) , it downloads the source code of each module, builds it using cmake and copies the resulting binaries to /opt/plutonium/modules. Every plutonium release has fiza bundled with it.
# Contributing
If you have a plutonium module that you want to be available to plutonium users via fiza , you can add it to packages/packages.txt. Fork this repo and add a new line to packages/packages.txt for your module. The line should have format: ```
name repoUrl tagName```
Make sure the name is unique. Your repo must have the tag that you added to packages.txt. The repo must also have two dll files added as binaries under the tag name you added in packages.txt. The names of dll files must be yourModuleName-win32.dll and yourModuleName-win64.dll .Make sure these dlls are linked statically C/C++ runtime and any other libraries. To support building from source, your repo must a have CMake script. Make sure this script works with CMake version 3.16.3 and later versions.
Make sure to save packages.txt using LF as line separator. After doing all this , you can send a pull request. Once approved, you can test your module installation using fiza
## Windows
```
cd C:\plutonium
plutonium fiza.plt update
plutonium fiza.plt install yourModule
```
## Linux
```bash
fiza update
fiza install yourModule
```
