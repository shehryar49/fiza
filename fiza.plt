# Plutonium Package Manager
# Written by Shahryar Ahmad
# 10 Feb 2022

import std/algo.plt
#import libcurl as lc
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
function installPackage(var name)
{
  println("installing from ",name)
  return nil
  var c = nil #lc.Curl()
  #c.setopt(lc.OPT_URL,"https://plutonium-lang.000webhostapp.com/downloads/modules/"+name+"/"+os+"/"+name+".dll")
  #c.setopt(lc.OPT_FOLLOWLOCATION,1)
  #c.setopt(lc.OPT_WRITEFUNCTION,WriteMemory)
  try
  {
    openedFile = open("C:\\plutonium\\modules\\"+name+".dll","wb")
  }
  catch(err)
  {
     println(err.msg)
     exit()
  }

  for(var i=1 to 3 step 1)
  {
    println("Starting download in ",4-i)
    sleep(1000)
    system("cls")
  }
  var res = c.perform()
  #if(res != lc.CURLE_OK)
  #{
    #println("Installation Failed: ",lc.strerror(res))
   # exit()
  #}
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
  installPackage(url)
}
else if(action == "remove")
  removePackage(name)
else
{
  println("Invalid action specified.See DOCS")
}
