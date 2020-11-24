  
#include <stdio.h>
#include <stdlib.h>
#ifndef __Hard_coded_data 
#define __Hard_coded_data 
#include "HardCodedData.h"
#include <Windows.h>
#endif

int moudlo(int num, int base);
void CheakArgs(int argc);
void CheakHandle(HANDLE my_handle);
void CheakAlocation(void* p_arr);
void valid_PTR(void*);
void CloseFileWrap(HANDLE file);
void SetFilePointerWrap(HANDLE input_file, uli start_pos, DWORD mode);
char* ReadFileWrap(DWORD len, HANDLE file);
void WriteFileWrap(HANDLE hFile, LPCVOID  lpBuffer, DWORD  nNumberOfBytesToWrite);
HANDLE OpenFileWrap( LPCSTR str, DWORD mode);
void read_number_of_line_and_end_of_lines(HANDLE file, PDWORD OUT num_of_lines_out,  OUT uli** p_end_of_lines);
BOOL CheakIsAnumber(char* str);
