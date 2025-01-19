#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<iostream>
#include"SetErrorMsgText.h"
#include<WinSock2.h>
#include <string>

#pragma comment(lib, "WS2_32.lib")

int main() {
	SOCKET sock;
	WSADATA wsaData;

	try
	{
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) {
			throw SetErrorMsgText("Startup: ", WSAGetLastError());
		}
		if ((sock = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET) {
			throw SetErrorMsgText("Socket: ", WSAGetLastError());
		}

		SOCKADDR_IN server;
		server.sin_family = AF_INET;
		server.sin_port = htons(2000);
		server.sin_addr.s_addr = inet_addr("127.0.0.1");

		if (connect(sock, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
			throw SetErrorMsgText("Error Connect: ", WSAGetLastError());
		}

		char ibuf[50] = "server: All Correct";
		int  libuf = 0, lobuf = 0;

		clock_t start = clock();

		int msgCount = 100;
		for (int i = 1; i <= msgCount; i++)
		{
			std::string obuf = std::to_string(i) + ") I am client";

			if ((lobuf = send(sock, obuf.c_str(), strlen(obuf.c_str()) + 1, NULL)) == SOCKET_ERROR) {
				throw SetErrorMsgText("send: ", WSAGetLastError());
			}

			if ((libuf = recv(sock, ibuf, sizeof(ibuf), NULL)) == SOCKET_ERROR) {
				throw SetErrorMsgText("recv: ", WSAGetLastError());
			}

			std::cout << ibuf << std::endl;
		}
		const clock_t end = clock();
		const std::string obuf = "";

		if ((lobuf = send(sock, obuf.c_str(), strlen(obuf.c_str()) + 1, NULL)) == SOCKET_ERROR) {
			throw SetErrorMsgText("send: ", WSAGetLastError());
		}

		std::cout << "Time: " << (static_cast<double>(end - start) / CLK_TCK) << " c\n";

		if (closesocket(sock) == SOCKET_ERROR) {
			throw SetErrorMsgText("Close socket: ", WSAGetLastError());
		}
		if (WSACleanup() == SOCKET_ERROR) {
			throw SetErrorMsgText("Cleanup: ", WSAGetLastError());
		}
	}
	catch (std::string errorMsg)
	{
		std::cout << std::endl << errorMsg;
		return 1;
	}

	return 0;
}