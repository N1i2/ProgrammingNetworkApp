#pragma once

#include <iostream>
#include <string>
#include <ctime>

#include<winsock2.h>

#pragma comment(lib, "WS2_32.lib")


std::string GetErrorMsgText(int errorCode);
std::string SetErrorMsgText(std::string msgText, int code);