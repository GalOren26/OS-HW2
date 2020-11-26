#include "Functions.h"
#include <assert.h>
#include < stdlib.h >



// ******** valiation of data and parms ************ 
	int moudlo(int num, int base)
	{
		return ((num % base) + base) % base;
	}
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

	void valid_PTR(void* ptr )
	{
		if (!ptr)
		{
			printf(" invalid input pointer parm");
			exit(INVALID_INPUT_PARM_EMPTY_POINTER);
		}
	}

	void FreeHandelsArray(HANDLE* handels, int len)
	{
		CheakArgs(handels);
		for (int i = 0; i < len;i++)
		{
			CloseHandleWrap(handels[i]);
		}
	}

	void CheakAlocation(void* p_arr)
	{
		if (p_arr == NULL) {
			printf_s("MEMORY_ALLOCATION_FAILURE.\n");
			exit(MEMORY_ALLOCATION_FAILURE);
		}
	}
	void CheakHandle(HANDLE my_handle)
	{
		if (my_handle == INVALID_HANDLE_VALUE)
		{
			printf_s("INVALID_HANDLE. error code %d", GetLastError());
			exit(INVALID_HANDLE_VALUE);
		}
	}

	BOOL CheakIsAnumber(char* str)
	{
		valid_PTR(str);
		/*This function cheak if string is a number - used for validate the value of key in this code */
		for (int i = 0; str[i] != '\0'; i++)
		{
			if (!isdigit(str[i]))
			{
				return FALSE;
			}
		}
		return TRUE;
	}
//****************File methods**************

	

	void read_number_of_line_and_end_of_lines(HANDLE file, PDWORD OUT num_of_lines_out, OUT uli** p_end_of_lines_out)
	{
		/*return the  number of line in file  and the places in the file of each  end of line */

		CheakHandle(file);
		// cheak_file_size_in_order to read file.
		LARGE_INTEGER  len_li;
		if (GetFileSizeEx(file, &len_li) == 0)
		{
			printf("empty file . error code %d", GetLastError());
			exit(EMPTY_FILE);
		}
		if (len_li.u.HighPart != 0)
		{	//asume file not more than 4gb 
			printf("File is Too big need to be less then 4 GB !");
			exit(FILE_IS_TOO_BIG);
		}
		DWORD len = len_li.u.LowPart;
		char* my_file_buff = calloc(len, sizeof(char));
		CheakAlocation(my_file_buff);
		ReadFileWrap(len, file, my_file_buff);
		DWORD num_of_lines = 0; 
		/* allocatre array to store end of lines, size bounded by the size of file and after fill will be shrink.*/
		uli* p_end_of_lines_temp = calloc( len, sizeof(uli));
		CheakAlocation(p_end_of_lines_temp);
		uli place = 0; 
		DWORD pos_in_file;
		for (pos_in_file = 0; pos_in_file < len; pos_in_file++)
		{
			if (my_file_buff[pos_in_file] == '\n')
			{
				num_of_lines++;
				p_end_of_lines_temp[place++] = pos_in_file;
			}
		}
		if (my_file_buff[len - 1] != '\n')// cheak if last line is without new line
		{
			num_of_lines++;
			p_end_of_lines_temp[place++] = pos_in_file-1;

		}
		uli* p_end_of_lines = calloc(place, sizeof(uli));
		CheakAlocation(p_end_of_lines);
		memcpy(p_end_of_lines, p_end_of_lines_temp, sizeof(uli) *place);
		free(p_end_of_lines_temp); 
		free(my_file_buff);
		*num_of_lines_out = num_of_lines;
		*p_end_of_lines_out = p_end_of_lines;
	}

	HANDLE OpenFileWrap( LPCSTR str, DWORD mode)
	{
		//CreateFileA wrap 
		HANDLE hFile;
		hFile = CreateFileA(str, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ| FILE_SHARE_WRITE, NULL, mode, FILE_ATTRIBUTE_NORMAL, NULL);
		CheakHandle(hFile);
		return hFile;
	}
	
	void FreeArray(void** arr, int len)
	{
		CheakArgs(arr);
		for (int i = 0; i < len;i++)
		{
			free(arr[i]);
		}
		free(arr);
	}

	void CloseHandleWrap(HANDLE file)
	{
		//CloseHandle wrap 
		BOOL  file_status = CloseHandle(file);
		if (!file_status)
		{
			printf("Failed to close file.error code %d", GetLastError());
			//not exit couse try best effort to close more files. 
		}
	}

	void SetFilePointerWrap(HANDLE input_file, uli start_pos, DWORD mode)
	{
		DWORD retval = SetFilePointer(input_file, start_pos, NULL, mode);

		if (retval == INVALID_SET_FILE_POINTER)
		{
			printf("INVALID_SET_FILE_POINTER");
			exit(INVALID_SET_FILE_POINTER);
		}
	}

	int  ReadFileWrap(DWORD len, HANDLE file,char* my_file_buff )
	{
		//WRAP TO ReadFile 
	
		DWORD lpNumberOfBytesRead = 0;
		if (ReadFile(file, (LPVOID)my_file_buff, len, &lpNumberOfBytesRead, NULL) == 0)
		{
			printf("error read file . error code %d", GetLastError());
			return ERROR_READ_FILE;
		}
		return SUCCESS;
	}

	void WriteFileWrap(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite)
	{
		DWORD lpNumberOfBytesRead = 0;
		if (WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, &lpNumberOfBytesRead, NULL) == 0)
		{
			printf("error write file . error code %d", GetLastError());
			exit(ERROR_WRITE_FILE);
		}
	}

	void find_dest_path(const char* source_path,OUT char ** dest_out )
	{
		/* find the dest path of where to save the decrypted.txt  ootput file rather source path is absulte or realative
put the result in dest ptr TO-do  free dest outside */
		char* dest;
		valid_PTR((void*)source_path);
		char* p_abs_path = strrchr(source_path, '\\');
		char* p_explicit_file = "decrypted.txt";
		size_t explicit_file_len = strlen(p_explicit_file);
		size_t abs_path_len = p_abs_path == NULL ? 0 : p_abs_path - source_path;
		dest = calloc( explicit_file_len + abs_path_len + ADDITION_LEN_TO_PATH, sizeof(char));
		CheakAlocation((void*)dest);
		if (p_abs_path)
		{
			memcpy(dest, source_path, abs_path_len);
			dest[abs_path_len] = '\\';
		}
		strcat_s(dest, explicit_file_len + abs_path_len + ADDITION_LEN_TO_PATH, p_explicit_file);
		*dest_out = dest;
	}

