
#include "HardCodedData.h"
#include "Functions.h"
#include "ThrredFuncs.h"


int main(int argc, char* argv[])
{
	CheakArgs(argc);
	HANDLE InputHandle;
	// TO-DO chaek if  input is valid path 
	LPCSTR input_path = argv[1];
	BOOL ret1 = CheakIsAnumber(argv[2]);
	BOOL ret2 = CheakIsAnumber(argv[3]);
    int operation= CheckOperation(argv[4]);
	if (ret1 == FALSE|| ret2 == FALSE)
	{
		printf("key or num of threads  is not a number  :(");
		return NOT_A_NUMBER;
	}
	uli key = atoi(argv[2]);
	int num_of_threads = atoi(argv[3]);
	if (num_of_threads <0 || num_of_threads> MAXIMUM_WAIT_OBJECTS)
	{
		printf("Invalid number of Threads");
		return(NOT_VALID_INPUT);
	}
	DWORD mode = OPEN_EXISTING;
	InputHandle = OpenFileWrap(input_path, mode);
	DWORD num_of_lines = 0;
	uli* end_of_lines = 0;
	read_number_of_line_and_end_of_lines(InputHandle, &num_of_lines, &end_of_lines);
	CloseHandleWrap(InputHandle);
	//return output path 
	char* dest_path;
	find_dest_path(input_path, &dest_path, operation);

	// TO-DO ADJUST TO  EACH TERAD IN FOR LOOP LATER 
	parssing_data params = {
		0,
		end_of_lines[num_of_lines - 1],
		dest_path,
		input_path,
		key ,
		operation
	};
	Createmultiplethreads(num_of_threads, num_of_lines, end_of_lines, &params);
	free(dest_path);

}
