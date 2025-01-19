#include "stdafx.h"

#define MSNAME L"\\\\.\\mailslot\\Box"

int main() {
	HANDLE hM;
	DWORD wb;

	char obuf[50];

	try
	{
		if ((hM = CreateFile(MSNAME,
			GENERIC_WRITE,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			NULL, NULL)) == INVALID_HANDLE_VALUE) {
			throw SetErrorMsgText("Error: Create:", GetLastError());
		}
		
		for (int i = 0; i < 1000; i++)
		{
			string ostr = to_string(i+1) + ") Hello";
			strcpy_s(obuf, ostr.c_str());

			if (!WriteFile(hM,
				obuf,
				sizeof(obuf),
				&wb,
				NULL)) {
				throw SetErrorMsgText("Error: Read:", GetLastError());
			}
		}

		strcpy_s(obuf, "stop");
		if (!WriteFile(hM,
			obuf,
			sizeof(obuf),
			&wb,
			NULL)) {
			throw SetErrorMsgText("Error: Read stop:", GetLastError());
		}

		cout << "All Correct" << endl;

		CloseHandle(hM);
	}
	catch (string errorText)
	{
		cout << endl << errorText << endl;
	}
}