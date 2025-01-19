#include "stdafx.h"

#define MSNAME L"\\\\.\\mailslot\\Box"

int main() {
	HANDLE hM;
	DWORD rb;
	DWORD timeWaiting = 180'000;

	char rbuf[300];
	bool flag = true;

	clock_t start, end;

	try
	{
		if ((hM = CreateMailslot(MSNAME,
			300,
			MAILSLOT_WAIT_FOREVER,
			NULL)) == INVALID_HANDLE_VALUE) {
			throw SetErrorMsgText("Error: Create mailslot", GetLastError());
		}

		cout << "Server is waiting..." << endl;

		while (true)
		{
			if (ReadFile(hM,
				rbuf,
				sizeof(rbuf),
				&rb,
				NULL)) {
				cout << rbuf << endl;

				if (flag) {
					start = clock();
					flag = false;
				}
			}
			else {
				throw SetErrorMsgText("Error: Read file", GetLastError());
			}

			if (strcmp(rbuf, "stop") == 0) {
				end = clock();
				cout << "Time: " << ((double)(end - start) / CLK_TCK) << endl;
				flag = true;
				cout << endl << "Server is waiting..." << endl;
			}
		}

		CloseHandle(hM);
	}
	catch (string errorText)
	{
		cout << endl << errorText << endl;
	}
}