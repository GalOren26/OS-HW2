
#include "HardCodedData.h"
#include "Functions.h"
#include "ThrredFuncs.h"
int main(int argc, char* argv[])
{

	HANDLE InputHandle;
	// TO-DO chaek if  input is valid path 
	LPCSTR input_path = argv[1];
	BOOL ret = CheakIsAnumber(argv[2]);
	if (ret == FALSE)
	{
		printf("key is not a number  :(");
		return NOT_A_NUMBER;
	}
	uli key = atoi(argv[2]);
	DWORD mode = OPEN_EXISTING;
	InputHandle = OpenFileWrap(input_path, mode);
	DWORD num_of_lines = 0;
	uli* end_of_lines = 0;
	read_number_of_line_and_end_of_lines(InputHandle, &num_of_lines, &end_of_lines);
	CloseHandleWrap(InputHandle);
	//return output path 
	char* dest_path;
	find_dest_path(input_path, &dest_path);

	// TO-DO ADJUST TO  EACH TERAD IN FOR LOOP LATER 
	parssing_data params = {
		0,
		end_of_lines[num_of_lines - 1],
		dest_path,
		input_path,
		key 
	};
	if (argv[3] <0 || argv[3]> MAXIMUM_WAIT_OBJECTS || !CheakIsAnumber(argv[3]))
	{
		printf("Invalid number of Threads");
		free(dest_path);
		return(NOT_VALID_INPUT);
	}
	int num_of_threads = argv[3];
	Createmultiplethreads(num_of_threads, num_of_lines, end_of_lines, &params);
	free(dest_path);
}
