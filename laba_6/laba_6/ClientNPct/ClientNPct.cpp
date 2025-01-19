#include "stdafx.h"

#define PIPE_NAME L"\\\\.\\pipe\\Tube"

int main() {
	cout << "ClientHPct" << endl;

	DWORD ps;

	try
	{
		char ibuf[50];
		char obuf[50] = "Hello ClientHPct";
		
		if (!CallNamedPipe(PIPE_NAME,
			obuf,
			sizeof(obuf),
			ibuf,
			sizeof(ibuf),
			&ps,
			NULL)) {
			throw SetErrorMsgText("Call: ", GetLastError());
		}
		else {
			cout << ibuf << endl;
		}
	}
	catch (string ErrorText)
	{
		cout << endl << ErrorText << endl;
	}

	return 0;
}