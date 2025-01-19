#pragma once

#include <iostream>
#include <WinSock2.h>
#include <string>
#include <ctime>

#pragma comment(lib, "WS2_32.lib")

std::string GetErrorMsgText(int errorCode);
std::string SetErrorMsgText(std::string msgText, int code);