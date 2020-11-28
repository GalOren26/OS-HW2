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

//input: the parsing data structure, including the operation mode, it decodes and encode strings by blocks depending on the operation mode.
int Dec_Enc_Block(parssing_data* p_params);

//input: the core decryption function that decodes by chars.
int Decryption(char* coded, uli end_of_block, uli key);

//input:the core encryption function that encodes by chars.
int Encryption(char* coded, uli end_of_block, uli key);
//function that takes the threads input and creates threads and includes waiting for multiple signals.
int Createmultiplethreads(int num_of_threads, uli num_of_lines, uli* end_of_lines, parssing_data* params);

//took from the Recritation, the wrap of create threads function.
static int CreateThreadSimple(LPTHREAD_START_ROUTINE p_start_routine,
	LPVOID p_thread_parameters,
	LPDWORD p_thread_id, HANDLE* OUT thread_handle);