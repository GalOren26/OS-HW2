  
#include <stdio.h>
#include <stdlib.h>
#ifndef __Hard_coded_data 
#define __Hard_coded_data 
#include "HardCodedData.h"
#include <Windows.h>
#endif
//#define CheakAlocation(thread_params) if(thread_params == NULL){ printf_s("MEMORY_ALLOCATION_FAILURE.\n"); exit(MEMORY_ALLOCATION_FAILURE); } 
//#define CheakHandle(my_handle) if (my_handle == INVALID_HANDLE_VALUE){printf_s("INVALID_HANDLE. error code %d", GetLastError());exit(INVALID_HANDLE_VALUE);}

int moudlo(int num, int base);
//input 
void CheakArgs(int argc);
BOOL CheakIsAnumber(char* str);
int valid_PTR(void*);
int CheckOperation(char* operation, int* modeflag);
//files
int OpenFileWrap(LPCSTR str, DWORD mode, HANDLE* OUT hFile);
int ReadFileWrap(DWORD len, HANDLE file, char* my_file_buff);
// set EOF at the end of the input file 
int SetEndOfFileWarp(LPCSTR output_path, uli end_pos, DWORD mode);
int SetFilePointerWrap(HANDLE input_file, uli pos, DWORD mode);
int WriteFileWrap(HANDLE hFile, LPCVOID  lpBuffer, DWORD  nNumberOfBytesToWrite);
int read_number_of_line_and_end_of_lines(HANDLE file, PDWORD OUT num_of_lines_out,  OUT uli** p_end_of_lines);
int find_dest_path(const char* source_path, OUT char** dest_out, int opreation);
//aray and and handles 
int  CheakAlocation(void* p_arr);
int CheakHandle(HANDLE my_handle);
int CloseHandleWrap(HANDLE file);
void FreeArray(void** arr, int len);
void FreeHandelsArray(HANDLE* handels, int len);
//process and threads 
int WaitForSingleObjectWrap(HANDLE handle, uli time);
//semphoros
int CreateSemphoreWrap(int num_of_therads,HANDLE * OUT semphore  );
int OpenSemphoreWrap( HANDLE * OUT semphore, const char* name);

//memory mengment 
//int setup_memory_menagment(MemoryTracker* OUT MemTracker);
//int push_element_memory_mangment(MemoryTracker*  MemTracker, MemoryTracker element);
//int FreeAll(MemoryTracker * memory_traker);











