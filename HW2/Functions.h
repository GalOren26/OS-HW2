  
#include <stdio.h>
#include <stdlib.h>
#ifndef __Hard_coded_data 
#define __Hard_coded_data 
#include "HardCodedData.h"
#include <Windows.h>
#endif
#define CheakAlocation(thread_params) if(thread_params == NULL){ printf_s("MEMORY_ALLOCATION_FAILURE.\n"); exit(MEMORY_ALLOCATION_FAILURE); } 
#define CheakHandle(my_handle) if (my_handle == INVALID_HANDLE_VALUE){printf_s("INVALID_HANDLE. error code %d", GetLastError());exit(INVALID_HANDLE_VALUE);}


int moudlo(int num, int base);
void CheakArgs(int argc);
//void CheakHandle(HANDLE my_handle);
//void  CheakAlocation(void* p_arr);
void valid_PTR(void*);
void FreeHandelsArray(HANDLE* handels, int len);
void FreeArray(void** arr, int len);
void CloseHandleWrap(HANDLE file);
void SetFilePointerWrap(HANDLE input_file, uli pos, DWORD mode);
int ReadFileWrap(DWORD len, HANDLE file, char* my_file_buff);
void WriteFileWrap(HANDLE hFile, LPCVOID  lpBuffer, DWORD  nNumberOfBytesToWrite);
HANDLE OpenFileWrap( LPCSTR str, DWORD mode);
void read_number_of_line_and_end_of_lines(HANDLE file, PDWORD OUT num_of_lines_out,  OUT uli** p_end_of_lines);
BOOL CheakIsAnumber(char* str);
