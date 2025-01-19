#pragma once

#include <algorithm>
#include <iostream>
#include <string>

#include "Winsock2.h"

std::string GetErrorMsgText(int errorCode);
std::string SetErrorMsgText(std::string msgText, int code);