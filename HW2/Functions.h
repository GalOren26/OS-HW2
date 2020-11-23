  
#include <stdio.h>
#include <stdlib.h>
#ifndef __Hard_coded_data 
#define __Hard_coded_data 
#include "HardCodedData.h"
#include <Windows.h>
#endif

void CheakArgs(int argc);
void CloseFileWrap(HANDLE file);
HANDLE OpenFileWrap( LPCSTR str, DWORD mode);
void CheakAlocation(void* p_arr);

