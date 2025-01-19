#pragma once

#include "Winsock2.h"
#pragma comment(lib, "WS2_32.lib") 

#include <iostream>
#include <string>
#include <tchar.h>

using namespace std;

std::string SetErrorMsgText(std::string msgText, int code);
std::string GetErrorMsgText(int errorCode);