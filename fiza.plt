#!/usr/bin/plutonium
# Plutonium Package Manager
# Written by Shahryar Ahmad
# 10 Feb 2022

import std/algo.plt
import libcurl as lc


var openedFile = nil
var size = 0

function WriteMemory(var bytes)
{
  system("cls")
  size+=len(bytes)
  println("Downloaded ",size, " bytes ")
  fwrite(bytes,openedFile)
}
function installPackage(var name,var url,var ver)
{

  if(@os == "Windows 32 bit" or @os == "Windows 64 bit")
  {
    # download dll from repo
    if(@os == "Windows 64 bit")
      url = url + "/releases/download/"+ver+"/"+name+"-win64.dll"
    else
      url = url + "/releases/download/"+ver+"/"+name+"-win32.dll"
    var c = lc.Curl()
    c.setopt(lc.OPT_URL,url)
    c.setopt(lc.OPT_FOLLOWLOCATION,1)
    c.setopt(lc.OPT_WRITEFUNCTION,WriteMemory)
    openedFile = open("C:\\plutonium\\modules\\"+name+".dll","wb")
    var res = c.perform()
    if(res != lc.CURLE_OK)
    {
      println(lc.strerror(res))
      return 0
    }
  }
  else # unix like systems (install from source)
  {
    #https://github.com/shehryar49/repo/archive/refs/tags/1.0.0.tar.gz
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
function updatePackageList()
{
  var c = lc.Curl()
  c.setopt(lc.OPT_URL,"https://raw.githubusercontent.com/shehryar49/fiza/main/packages/packages.txt")
  c.setopt(lc.OPT_FOLLOWLOCATION,1)
  c.setopt(lc.OPT_WRITEFUNCTION,lc.WriteMemory)
  var res = c.perform()
  if(res != lc.CURLE_OK)
  {
    println("Error updading package list.")
    println(lc.strerror(res))
    return nil
  }
  var file = nil
  if(@os == "Windows 64 bit" or @os == "Windows 32 bit")
    file = open("C:\\plutonium\\fiza\\packages.txt","wb")
  else
    file = open("/opt/plutonium/fiza/packages.txt","wb")
  fwrite(c.data,file)
  close(file)
  println("Updated package list successfully!")
}

#########
if(len(argv) == 1 and argv[0] == "update")
{
  updatePackageList()
  exit()
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

if(action == "install")
{
  var srcfile = nil
  if(@os == "Windows 64 bit" or @os == "Windows 32 bit")
    srcfile = open("C:\\plutonium\\fiza\\packages.txt","r")
  else
    srcfile = open("/opt/plutonium/fiza/packages.txt","r")
  var lines = readlines(srcfile)
  var url = nil
  var ver = nil
  foreach(var line: lines)
  {
    var parts = split(line," ")
    if(parts[0] == name)
    {
      url = parts[1]
      ver = parts[2]
    }
    
  }
  if(url == nil)
  {
    println("Package ",name," was not found!")
    exit()
  }
  installPackage(name,url,ver)
}
else if(action == "remove")
  removePackage(name)
else
  println("Invalid action specified.See DOCS")