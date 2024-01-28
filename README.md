# fiza
A simple package manager for [zuko programming language](https://github.com/shehryar49/zuko)
Fiza allows you to install zuko modules(native modules) on all supported platforms conveniently. It does so by downloading zuko modules from github repos. Every module has it's own repo. On Windows, it downloads module binaries(dll files) and places them in C:\zuko\modules . On Unix like systems (Linux and Mac OS) , it downloads the source code of each module, builds it using cmake and copies the resulting binaries to /opt/zuko/modules. Every zuko release has fiza bundled with it.
# Contributing
If you have a zuko module that you want to be available to zuko users via fiza , you can add it to packages/packages.txt. Fork this repo and add a new line to packages/packages.txt for your module. The line should have format: ```
name repoUrl tagName```
Make sure the name is unique. Your repo must have the tag that you added to packages.txt. The repo must also have two dll files added as binaries under the tag name you added in packages.txt. The names of dll files must be yourModuleName-win32.dll and yourModuleName-win64.dll .Make sure these dlls are linked statically C/C++ runtime and any other libraries. To support building from source, your repo must a have CMake script. Make sure this script works with CMake version 3.16.3 and later versions.
Make sure to save packages.txt using LF as line separator. After doing all this , you can send a pull request. Once approved, you can test your module installation using fiza
## Windows
```
cd C:\zukk
zuko fiza.zk update
zuko fiza.zk install yourModule
```
## Linux
```bash
fiza update
fiza install yourModule
```
