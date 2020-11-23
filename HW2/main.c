
#include "HardCodedData.h"
#include "Functions.h"
int main(int argc, char * argv [])
{
	HANDLE InputHandle;
	LPCSTR str = argv[1];
	DWORD mode = OPEN_EXISTING;
	InputHandle=OpenFileWrap(str, mode);

	//return output path 
	char * p_abs_path= strrchr(str, '\\' ); 
	char* p_explicit_file = "decrypted.txt";
	int explicit_file_len = strlen(p_explicit_file);
	int abs_path_len =  p_abs_path == NULL? 0: p_abs_path - str;
	char* dest = calloc(explicit_file_len + abs_path_len+ ADDITION_LEN_TO_PATH, sizeof(char));
	CheakAlocation((void*)dest);
	if (p_abs_path)
	{
		memcpy(dest, str, abs_path_len);
		dest[abs_path_len] = '\\';
	}

	strcat_s(dest, explicit_file_len +abs_path_len+ ADDITION_LEN_TO_PATH, p_explicit_file);
	mode = CREATE_ALWAYS;
	OpenFileWrap(dest, mode);

	CloseFileWrap(InputHandle);
}
