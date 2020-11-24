#include "Functions.h"
#include "ThrredFuncs.h"
#include <assert.h>
#include < stdlib.h >

//****************encryption decryption  methods**************

void decrypt_block(parssing_data* p_params)
{

	/* the function  Decrypt file by positiong in the file and parms -
	used to implement stage 1 and help for  the threads later.*/

	 HANDLE input_file= OpenFileWrap(p_params->input_path, OPEN_EXISTING);
	 CheakHandle(input_file); 
	 SetFilePointerWrap(input_file, p_params->start_pos, FILE_BEGIN);
	 DWORD len = p_params->end_pos- p_params->start_pos+1;
	 char* my_file_buff = ReadFileWrap(len,input_file);
	 Decryption(my_file_buff, p_params->num_of_lines, p_params->key);

	// write to file 
	 HANDLE output_file  = OpenFileWrap(p_params->output_path, CREATE_ALWAYS);
	 CheakHandle(output_file);
	 SetFilePointerWrap(output_file, p_params->start_pos, FILE_BEGIN);
	 WriteFileWrap(output_file, (LPVOID)my_file_buff, len);
	 free(my_file_buff);
	 CloseFileWrap(input_file);
	 CloseFileWrap(output_file);
}

void Decryption(char* coded,uli number_of_lines, uli key)
{
	// function for Decryption and enctyption 
	valid_PTR(coded);
	int i = 0;
	char ch;
	uli counter_liens = 0;
	while (counter_liens < number_of_lines)
	{
		for (i = 0; coded[i] != '\n'; i++) { // run over all the string
			ch = coded[i];
			if (ch >= 'a' && ch <= 'z')
			{ 
				coded[i]='a'+moudlo(ch - 'a' - key, 26);
			}
			if (ch >= 'A' && ch <= 'Z')
			{ 
				coded[i] = 'A' +moudlo(ch - 'A' - key, 26);
			}
			if (ch >= '0' && ch <= '9')
			{ 
				coded[i] = '0' + moudlo(ch - '0' - key, 10);
			}
		}
		counter_liens++;
	}
	// printf("Decrypted message: %s \n", coded);
}

