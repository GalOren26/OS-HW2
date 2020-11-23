#include "Functions.h"
#include <assert.h>
void CheakArgs(int argc)
{
	if (argc < 3)
	{
		printf("ERROR: Not enough input arguments");
		exit(ERR_CODE_NOT_ENOUGH_ARGUMENTS);
	}
	if (argc > 3)
	{
		printf("ERROR: Too many input arguments");
		exit(ERR_CODE_TOO_MANY_ARGUMENTS);
	}
}
	void CloseFileWrap(HANDLE file)
	{
		BOOL  file_status = CloseHandle(file);
		if (file_status)
		{
			printf("Failed to close file.error code %d", GetLastError());
			//not exit couse try best effort to close more files. 
		}
	}
	//CreateFileA wrap 
	HANDLE OpenFileWrap( LPCSTR str, DWORD mode)
	{

		HANDLE hFile;
		hFile = CreateFileA(str, GENERIC_READ, FILE_SHARE_READ, NULL, mode, FILE_ATTRIBUTE_NORMAL, NULL);
	 	  if (hFile == INVALID_HANDLE_VALUE)
			{
				printf_s("Failed to open file. error code %d",GetLastError());
				exit(INVALID_HANDLE_VALUE);
			}
			return hFile;
	}

	void CheakAlocation(void* p_arr)
	{
		if (p_arr == NULL) {
			printf_s("MEMORY_ALLOCATION_FAILURE.\n");
			exit(MEMORY_ALLOCATION_FAILURE);
		}
	}



	char* Decryption(char* coded, int key)
	{
		int i = 0;
		char ch;
		for (i = 0; coded[i] != '\0'; i++) { // run over all the string
			ch = coded[i];
			if (ch >= 'a' && ch <= 'z')
			{ // for cyclic purposes
				if ((ch - 'a' - key) >= 0)
				{
					ch = 'a' + ((ch - 'a' - key) % 26);
					coded[i] = ch;
				}
				else
				{
					ch = 'z' + ((ch - 'a' - key) % 26) + 1;
					coded[i] = ch;
				}
			}
			if (ch >= 'A' && ch <= 'Z')
			{ // for cyclic purposes
				if ((ch - 'A' - key) >= 0)
				{
					ch = 'A' + (ch - 'A' - key) % 26;
					coded[i] = ch;
				}
				else
				{
					ch = 'Z' + ((ch - 'A' - key) % 26) + 1;
					coded[i] = ch;
				}
			}
			if (ch >= '0' && ch <= '9')
			{ // for cyclic purposes
				if ((ch - '0' - key) >= 0)
				{
					ch = '0' + (ch - '0' - key) % 10;
					coded[i] = ch;
				}
				else
				{
					ch = '9' + ((ch - '0' - key) % 10) + 1;
					coded[i] = ch;
				}
			}
		}

		// printf("Decrypted message: %s \n", coded);
		return (coded);
	}
