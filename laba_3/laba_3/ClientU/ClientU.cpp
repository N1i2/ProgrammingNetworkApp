#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <clocale>
#include <ctime>

#include "stdafx.h"
#include "Winsock2.h"
#pragma comment(lib, "WS2_32.lib")

using namespace std;

int main()
{
    WSADATA wsaData;
    SOCKET cC;

    try 
    {
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            throw SetErrorMsgText("Startup: ", WSAGetLastError());
        }

        if ((cC = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET){
            throw  SetErrorMsgText("socket: ", WSAGetLastError());
        }

        SOCKADDR_IN serv;
        int ls = sizeof(serv);
        serv.sin_family = AF_INET;
        serv.sin_port = htons(2000);
        serv.sin_addr.s_addr = inet_addr("127.0.0.1");
        //serv.sin_addr.s_addr = inet_addr("192.168.6.162");

        clock_t start, end;
        char ibuf[50] = "server: connect ";
        int  libuf = 0, lobuf = 0;

        int countMessage;
        cout << "Count messages: ";
        cin >> countMessage;

        start = clock();
        for (int i = 1; i <= countMessage; i++) {
            string obuf = to_string(i) + ") Hello from Client " + "\n";

            if ((libuf = sendto(cC, obuf.c_str(), obuf.length() + 1, NULL, (SOCKADDR*)&serv, sizeof(serv))) == SOCKET_ERROR) {
                throw  SetErrorMsgText("sendto: ", WSAGetLastError());
            }

            cout << obuf;
        }
        end = clock();
        string obuf = "";

        if ((libuf = sendto(cC, obuf.c_str(), strlen(obuf.c_str()) + 1, NULL,
            (SOCKADDR*)&serv, sizeof(serv))) == SOCKET_ERROR)
        {
            throw  SetErrorMsgText("sendto: ", WSAGetLastError());
        }

        cout << "\nTIME: " << ((double)(end - start) / CLK_TCK) << " c" << endl;

        if (closesocket(cC) == SOCKET_ERROR){
            throw SetErrorMsgText("closesocket: ", WSAGetLastError());
        }
        if (WSACleanup() == SOCKET_ERROR){
            throw  SetErrorMsgText("Cleanup: ", WSAGetLastError());
        }
    }
    catch (string errorMsgText)
    {
        cout << endl << errorMsgText;
    }

    system("pause");
    return 0;
}
