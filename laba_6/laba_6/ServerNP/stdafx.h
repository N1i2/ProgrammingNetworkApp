#pragma once
#pragma comment(lib, "WS2_32.lib")

#include"Winsock2.h"

#include<iostream>
#include<string>
#include<tchar.h>

using namespace std;

std::string GetErrorMsgText(int errorCode);
std::string SetErrorMsgText(std::string msgText, int code);