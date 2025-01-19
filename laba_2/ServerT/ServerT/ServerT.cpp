#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include"SetErrorMsgText.h"
#include<winsock2.h>

#pragma comment(lib, "WS2_32.lib")

int main()
{
	SOCKET serverSock;
	WSADATA wsaData;

	try {
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) {
			throw SetErrorMsgText("WSAStartup failed: ", WSAGetLastError());
		}
		if ((serverSock = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET) {
			throw SetErrorMsgText("Socket failed: ", WSAGetLastError());
		}

		SOCKADDR_IN serv;
		serv.sin_family = AF_INET;
		serv.sin_port = htons(2000);
		serv.sin_addr.s_addr = INADDR_ANY;

		if (bind(serverSock, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR) {
			throw SetErrorMsgText("Bind: ", WSAGetLastError());
		}
		if (listen(serverSock, SOMAXCONN) == SOCKET_ERROR) {
			throw SetErrorMsgText("listen:", WSAGetLastError());
		}

		while (true) {
			std::cout << "Server is waiting ..." << "\n\n";

			SOCKET clineSock;
			SOCKADDR_IN clnt;
			int length = sizeof(clnt);
			memset(&clnt, 0, length);

			if ((clineSock = accept(serverSock, (sockaddr*)&clnt, &length)) == INVALID_SOCKET) {
				throw SetErrorMsgText("Accept: ", WSAGetLastError());
			}

			std::cout << "New User\n";
			std::cout << "Ip: " << inet_ntoa(clnt.sin_addr) << std::endl;
			std::cout << "Port: " << ntohs(clnt.sin_port) << std::endl << std::endl;

			clock_t start, end;
			char obuf[50] = "server: all correct ";
			bool flag = true;

			while (true)
			{
				try
				{
					int lobuf = 0;
					int libuf = 0;
					char ibuf[50];


					if ((libuf = recv(clineSock, ibuf, sizeof(ibuf), NULL)) == SOCKET_ERROR)
					{
						if (WSAGetLastError() == WSAECONNRESET)
						{
							end = clock();
							flag = true;
							break;
						}
						throw SetErrorMsgText("recv: ", WSAGetLastError());
					}
					if (flag)
					{
						start = clock();
						flag = !flag;
					}

					std::string obuf = ibuf;
					if ((lobuf = send(clineSock, obuf.c_str(), strlen(obuf.c_str()) + 1, NULL)) == SOCKET_ERROR) {
						throw SetErrorMsgText("send: ", WSAGetLastError());
					}

					if (strcmp(ibuf, "") == 0)
					{
						flag = true;
						end = clock();
						std::cout << "Time: " << ((double)(end - start) / CLK_TCK) << "\n\n";
						break;
					}
					std::cout << ibuf << std::endl;
				}
				catch (std::string errorMsg)
				{
					std::cout << errorMsg;
				}
			}
			if (closesocket(clineSock) == SOCKET_ERROR) {
				throw SetErrorMsgText("Close client socket: ", WSAGetLastError());
			}
		}	
		if (closesocket(serverSock) == SOCKET_ERROR) {
			throw SetErrorMsgText("Close server socket: ", WSAGetLastError());
		}
		if (WSACleanup() == SOCKET_ERROR) {
			throw SetErrorMsgText("WSACleanup: ", WSAGetLastError());
		}
	}
	catch (std::string errorMsg) {
		std::cout << "\nWSAGetLastError: " << errorMsg;
		return 1;
	}

	return 0;
}