#include "stdafx.h"

#define PIPE_NAME L"\\\\.\\pipe\\Tube"
#define NAME "ClientNP"

int main() {
	cout << NAME << endl;

	HANDLE hPipe;
	DWORD ps;

	try
	{
		if ((hPipe = CreateFile(PIPE_NAME,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			NULL,
			NULL)) == INVALID_HANDLE_VALUE) {
			throw SetErrorMsgText("Create: ", GetLastError());
		}

		const int COUNT_MSG = 100;
		char obuf[50];

		for (int i = 0; i < COUNT_MSG; i++)
		{
			string buf = to_string(i + 1) + ") Hello " + NAME;

			if (!WriteFile(hPipe, buf.c_str(), sizeof(buf), &ps, NULL)) {
				throw SetErrorMsgText("Write: ", GetLastError());
			}
			if (!ReadFile(hPipe, obuf, sizeof(obuf), &ps, NULL)) {
				throw SetErrorMsgText("Read: ", GetLastError());
			}
			else {
				cout << obuf << endl;
			}
		}

		CloseHandle(hPipe);
	}
	catch (string ErrorText)
	{
		cout << endl << ErrorText << endl;
	}

	return 0;
}