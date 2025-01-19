#include "stdafx.h"

#define PIPE_NAME L"\\\\.\\pipe\\Tube"

int main() {
	HANDLE hPipe;
	DWORD ps;

	try
	{
		if ((hPipe = CreateNamedPipe(PIPE_NAME,
			PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_MESSAGE | PIPE_WAIT,
			1, NULL, NULL,
			INFINITE, NULL)) == INVALID_HANDLE_VALUE) {
			throw SetErrorMsgText("create Pide: ", GetLastError());
		}

		while (true)
		{
			cout << "Server is wateing..." << endl;

			if (!ConnectNamedPipe(hPipe, NULL)) {
				throw SetErrorMsgText("Connect: ", GetLastError());
			}

			char buf[50];

			while (ReadFile(hPipe, buf, sizeof(buf), &ps, NULL))
			{
				cout << buf << endl;

				if (!WriteFile(hPipe, buf, sizeof(buf), &ps, NULL)) {
					throw SetErrorMsgText("Write: ", GetLastError());
				}
			}

			if (!DisconnectNamedPipe(hPipe)) {
				throw SetErrorMsgText("Disconnect: ", GetLastError());
			}

			cout << endl;
		}

		if (!CloseHandle(hPipe)) {
			throw SetErrorMsgText("Close: ", GetLastError());
		}
	}
	catch (string ErrorText)
	{
		cout << endl << ErrorText << endl;
	}

	return 0;
}