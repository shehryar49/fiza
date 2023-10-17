#!/usr/bin/plutonium
# Plutonium Package Manager
# Written by Shahryar Ahmad
# 10 Feb 2022

import std/algo.plt
import libcurl as lc
import regex

var openedFile = nil
var size = 0

function WriteMemory(var bytes)
{
  system("cls")
  size+=len(bytes)
  println("Downloaded ",size, " bytes ")
  fwrite(bytes,openedFile)
}
function installPackage(var name,var url)
{
  println("installing from ",name)
  if(@os == "Windows 32 bit" or @os == "Windows 64 bit")
  {
    # download dll from repo

  }
  else # unix like systems (install from source)
  {
    var ret = system("git clone "+url+" tmp")
    if(ret != 0)
    {
      println("git clone failed.")
      exit()
    }
    ret = system("cd tmp && cmake . -DCMAKE_BUILD_TYPE=Release && make && cd ..")
    if(ret != 0)
    {
      println("build failed")
      exit()
    }
    println("[+] Copying files")
    ret = system("sudo cp tmp/"+name+".so /opt/plutonium/modules && rm -rf tmp")
    if(ret != 0)
    {
      println("copy failed.")
      exit()
    }
  }
  println("Installation Done!")
}
function removePackage(var name)
{
  if(@os == "Windows 32 bit" or @os == "Windows 64 bit")
    system("del /F /Q C:\\plutonium\\modules\\"+name+".dll")
  else
    system("sudo rm /opt/plutonium/modules/"+name+".so")
}

if(len(argv) != 2)
{
  println("usage: plutonium fiza <action> <package>")
  println("Supported actions: ")
  println("\tinstall")
  println("\tremove")
  exit()
}
var action = argv[0]
var name = argv[1]
if(!regex.match(name,"[a-zA-Z]+[0-9]*"))
{
  println("Invalid package name")
  exit()
}
if(action == "install")
{
  var srcfile = open("packages/packages.txt","r")
  var lines = readlines(srcfile)
  var url = nil
  foreach(var line: lines)
  {
    var parts = split(line," ")
    if(parts[0] == name)
      url = parts[1]
    
  }
  if(url == nil)
  {
    println("Package ",name," was not found!")
    exit()
  }
  installPackage(name,url)
}
else if(action == "remove")
  removePackage(name)
else
{
  println("Invalid action specified.See DOCS")
}
