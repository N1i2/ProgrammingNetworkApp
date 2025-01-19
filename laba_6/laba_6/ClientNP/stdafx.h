#pragma once

#pragma comment(lib, "WS2_32.lib")

#include "WinSock2.h"

#include <iostream>
#include <string>
#include <tchar.h>

using namespace std;

std::string SetErrorMsgText(std::string msgText, int code);
std::string GetErrorMsgText(int errorCode);