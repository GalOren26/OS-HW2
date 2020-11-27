#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "HardCodedData.h"
#include <Windows.h>
typedef struct
{
	uli start_pos;
	uli end_pos;
	LPCSTR  output_path;
	LPCSTR input_path;
	uli key;
	int operation;
}parssing_data;


void find_dest_path(const char* source_path, OUT char** dest_path,int opeartion);
int Dec_Enc_Block(parssing_data* p_params);
void Decryption(char* coded, uli end_of_block, uli key);
void Encryption(char* coded, uli end_of_block, uli key);
void Createmultiplethreads(int num_of_threads, uli num_of_lines, uli* end_of_lines, parssing_data* params);
HANDLE CreateThreadSimple(LPTHREAD_START_ROUTINE p_start_routine,
	LPVOID p_thread_parameters,
	LPDWORD p_thread_id);