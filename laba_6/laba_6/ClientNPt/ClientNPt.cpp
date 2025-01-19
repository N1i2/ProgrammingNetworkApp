#include "stdafx.h"

#define PIPE_NAME L"\\\\.\\pipe\\Tube"
#define NAME "ClientHPt"

int main() {
	cout << NAME << endl;

	HANDLE hPipe;
	DWORD ps;
	DWORD ts = PIPE_READMODE_MESSAGE;

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
		if (!SetNamedPipeHandleState(hPipe, &ts, NULL, NULL)) {
			throw SetErrorMsgText("SetState: ", GetLastError());
		}

		const int COUNT_MSG = 100;
		char obuf[50];
		char ibuf[50];

		for (int i = 0; i < COUNT_MSG; i++)
		{
			string buf = to_string(i + 1) + ") Hello " + NAME;
			strcpy_s(obuf, buf.c_str());

			if (!TransactNamedPipe(hPipe,
				obuf,
				sizeof(obuf),
				ibuf,
				sizeof(ibuf),
				&ps,
				NULL)) {
				throw SetErrorMsgText("Transact: ", GetLastError());
			}
			else {
				cout << ibuf << endl;
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