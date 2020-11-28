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
	HANDLE* main_sem;
	HANDLE* thread_sem;
}parssing_data;

int Dec_Enc_Block(parssing_data* p_params);
int Decryption(char* coded, uli end_of_block, uli key);
int Encryption(char* coded, uli end_of_block, uli key);
int Createmultiplethreads(int num_of_threads, uli num_of_lines, uli* end_of_lines, parssing_data* params);
static int CreateThreadSimple(LPTHREAD_START_ROUTINE p_start_routine,
	LPVOID p_thread_parameters,
	LPDWORD p_thread_id, HANDLE* OUT thread_handle);