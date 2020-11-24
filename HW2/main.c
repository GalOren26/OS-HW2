
#include "HardCodedData.h"
#include "Functions.h"
#include "ThrredFuncs.h"
int main(int argc, char* argv[])
{
	HANDLE InputHandle;
	// TO-DO chaek if  input is valid path 
	LPCSTR path = argv[1];
	BOOL ret= CheakIsAnumber(argv[2]);
	if (ret == FALSE)
	{
		printf("key is not a number  :(");
		exit(NOT_A_NUMBER);
	}
	uli key=atoi(argv[2]);
	DWORD mode = OPEN_EXISTING;
	InputHandle = OpenFileWrap(path, mode);
	DWORD num_of_lines = 0;
	uli* end_of_lines = 0;
	read_number_of_line_and_end_of_lines(InputHandle, &num_of_lines, &end_of_lines);
	CloseFileWrap(InputHandle);
	//return output path 
	char* dest_path;
	find_dest_path(path, &dest_path);

	// TO-DO ADJUST TO  EACH TERAD IN FOR LOOP LATER 
	parssing_data parms = {
		0,
		end_of_lines[1],
		key,
		dest_path,
		path,
		1
	};
	decrypt_block(&parms);
	free(dest_path);
}
