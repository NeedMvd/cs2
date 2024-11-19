#pragma once
#include <memory>
#include <chrono>
#include <string>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <iostream>
#include <wininet.h>
#pragma comment(lib, "wininet.lib")
#include <vector>
using namespace std;
class Update final
{
public:
	string replaceAll2(std::string subject, const std::string& search, const std::string& replace);
	string DownloadString2(string URL);
	
private:
};
inline std::unique_ptr<Update> Updater = std::make_unique<Update>();