#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "HardCodedData.h"
#include <Windows.h>
typedef struct
{
	uli start_pos;
	uli end_pos;
	uli num_of_lines;
	LPCSTR  output_path;
	LPCSTR input_path;
	uli key;
}parssing_data;


void find_dest_path(const char* source_path, OUT char** dest_path);
void decrypt_block(parssing_data* params);
void Decryption(char* coded, uli number_of_lines, uli key);
