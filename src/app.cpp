#ifdef _WIN32
#define CURL_STATICLIB
#define _CRT_SECURE_NO_WARNINGS //fuck microsoft
#pragma comment(lib,"crypt32.lib")
#pragma comment(lib,"Normaliz.lib")
#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"Wldap32.lib")
#pragma comment(lib,"libcurl_a.lib")
#else
#include <unistd.h>
#endif
#include <iostream>
#include <string>
#include <string.h>
#include "consts.h"
#include "utils.h"
#include "fiza.h"

#include <curl/curl.h>


const char* USAGE_STR =
	"Fiza - package manager for Plutonium - " PLATFORM_STR "\n"
	"Usage:"
	"\tfiza <command> <package>\n"
	"\tvalid commands are:\n"
	"\tinstall\t\tInstall a package\n"
	"\tremove\t\tRemove a package\n"
	"\tlist-installed\tList all installed packages\n";
using namespace std;

static size_t write_data(void* ptr, size_t size, size_t nmemb, void* stream)
{
	size_t written = fwrite(ptr, size, nmemb, (FILE*)stream);
	return written;
}
int progress_callback(void *clientp,
                      curl_off_t dltotal,
                      curl_off_t dlnow,
                      curl_off_t ultotal,
                      curl_off_t ulnow)
{
	#ifndef DEBUG
		#ifdef _WIN32
		int ret = system("cls");
		#else
		int ret = system("clear");
		#endif
	#endif
	cout<<"Downloaded "<<dlnow<<" bytes"<<endl;
	return 0;
}
 
int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << USAGE_STR;
		exit(1);
	}
	std::string command = argv[1], packageName;
	if (command == "install" || command == "remove")
	{
		#ifdef __linux__
	      if(getuid())
	      {
	        std::cout<<"Run as root!"<<std::endl;
	        return 1;
	      }
    	#endif
		packageName = argv[2];
		if (!packageNameIsValid(packageName))
		{
			std::cerr << "Package name seems to be invalid.\n";
			exit(1);
		}
	}

	if (command == "install")
	{
		string url = REPO_URL;
		string outputPath;
        #ifdef _WIN64
		  url += "win64/" + packageName + ".dll";
		  outputPath = "C:\\plutonium\\modules\\" + packageName + ".dll";
        #elif defined _WIN32
		  url += "win32/" + packageName + ".dll";
		  outputPath = "C:\\plutonium\\modules\\" + packageName + ".dll";
        #else
		  url += "linux/" + packageName + ".tar.xz";
		  outputPath = "tmp.tar.xz";
        #endif
		FILE* fp = fopen(outputPath.c_str(), "wb");
		if (!fp)
		{
			perror("fopen: ");
			return 1;
		}
		#ifdef DEBUG
          cout<<url<<endl;
		#endif
		curl_global_init(CURL_GLOBAL_ALL);
		CURL* curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		char data;
		curl_easy_setopt(curl, CURLOPT_XFERINFODATA, &data);
        curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION,progress_callback);
		CURLcode res = curl_easy_perform(curl);
		if (res != CURLE_OK)
		{
			printf("[-] Installation failed: %s\n", curl_easy_strerror(res));
			return 1;
		}

		long code = 0;
		curl_easy_getinfo(curl,CURLINFO_HTTP_CODE, &code);
		if (code != 200)
		{
			std::cout<<"[-] Installation failed: HTTP Code "<<code<<"\n";
			return 1;
		}
		fclose(fp);
		curl_global_cleanup();
        #ifdef __linux__
		  std::cout<<"[+] Extracting archive"<<std::endl;
		  int ret = system("tar -xf tmp.tar.xz");
		  if(ret != 0)
		  {
			std::cout<<"[-] Installation failed."<<std::endl;
			return 1;
		  }
		  ret = system(("cd "+packageName+" && ./build.sh cd ..").c_str());
		  if(ret!=0)
		  {
			std::cout<<"[-] Installation failed at build step"<<std::endl;
			return 1;
		  }

		  ret = system(("cp "+packageName+"/"+packageName+".so /opt/plutonium/modules").c_str());
		  if(ret!=0)
		  {
			std::cout<<"[-] Failed to copy files!"<<std::endl;
			return 1;
		  }
		  ret = system(("rm -rf "+packageName).c_str());
		  ret |= system("rm tmp.tar.xz");
		  if(ret != 0)
		  {
			cout<<"[-] Unable to delete temporary files."<<endl;
		  }
        #endif
		std::cout<<"[+] Installation completed!"<<std::endl;
	}
	else if (command == "remove"){
		if (!packageIsInstalled(packageName)){
			std::cerr << packageName + " is not installed. Cannot remove\n";
			exit(1);
		}

		if (packageRemove(packageName)){
			std::cout<<"[+] "<<packageName << " was removed\n";
		}else{
			std::cerr<<"[-] " << packageName << " was not removed\n";
			exit(1);
		}

	}else if (command == "list-installed"){
		for (auto &name : packageListInstalled()){
			std::cout << name << "\n";
		}

	}else{
		std::cerr << USAGE_STR;
		exit(1);
	}
	return 0;
}
