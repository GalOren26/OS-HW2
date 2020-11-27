#include "Functions.h"
#include "ThrredFuncs.h"

#include <assert.h>
#include < stdlib.h >

//****************encryption decryption  methods**************

int decrypt_block(parssing_data* p_params)
{
	/* the function  Decrypt file by positiong in the file and parms -
	used to implement stage 1 and help for  the threads later.*/
	if (p_params->end_pos == p_params->start_pos)
	{
		return SUCCESS;
	}

	 HANDLE input_file= OpenFileWrap(p_params->input_path, OPEN_EXISTING);
	 CheakHandle(input_file); 
	 SetFilePointerWrap(input_file, p_params->start_pos, FILE_BEGIN);
	 DWORD len = p_params->end_pos- p_params->start_pos+1;
	 char* my_file_buff = calloc(len, sizeof(char));
	 CheakAlocation(my_file_buff);
	 int ret_val = ReadFileWrap(len,input_file, my_file_buff);
	 if (ret_val == ERROR_READ_FILE)
	 {
		 return ERROR_READ_FILE ;
	 }
	 Decryption(my_file_buff, len, p_params->key);

	// write to file 
	 HANDLE output_file = OpenFileWrap(p_params->output_path, OPEN_EXISTING);
	 if (output_file == ERROR_FILE_NOT_FOUND)
	 {
		 printf("problem with open destmation file ,error code %d", GetLastError());
		 exit(ERROR_FILE_NOT_FOUND);
	 }
	 SetFilePointerWrap(output_file, p_params->start_pos, FILE_BEGIN);
	 WriteFileWrap(output_file, (LPVOID)my_file_buff, len);
	 free(my_file_buff);	
	 CheakHandle(output_file);

	 CloseHandleWrap(input_file);
	 CloseHandleWrap(output_file);
	 return SUCCESS; 
}


void Decryption(char* coded,uli end_of_block, uli key)
{
	// function for Decryption and enctyption 
	valid_PTR(coded);
	char ch;
		for (uli i=0 ; i<= end_of_block; i++) { // run over all the string
			ch = coded[i];
			if (ch >= 'a' && ch <= 'z')
			{ 
				coded[i]='a'+moudlo(ch - 'a' - key, 26);
			}
			if (ch >= 'A' && ch <= 'Z')
			{ 
				coded[i] = 'A' +moudlo(ch - 'A' - key, 26);
			}
			if (ch >= '0' && ch <= '9')
			{ 
				coded[i] = '0' + moudlo(ch - '0' - key, 10);
			}
		}
}



DWORD WINAPI DecThread(LPVOID lpParam)
{
	parssing_data* params;
	params = (parssing_data*)lpParam;
	int ret_val =decrypt_block(params);
	assert(ret_val == SUCCESS);
	return  SUCCESS; 
}

void Createmultiplethreads(int num_of_threads, uli num_of_lines, uli* end_of_lines, parssing_data* p_params)
{
	//int num_of_threads = argv[3];
	valid_PTR(end_of_lines);
	valid_PTR(p_params);
	/*create params to thread */
	HANDLE* p_thread_handles = (HANDLE * )calloc(num_of_threads, sizeof(HANDLE)); // each cell in the array, contains params for thread
	CheakAlocation(p_thread_handles);

	DWORD* p_thread_ids = (DWORD * )calloc(num_of_threads, sizeof(DWORD)); // each cell in the array, contains params for thread
	CheakAlocation(p_thread_ids);
	parssing_data** thread_params = (parssing_data**)calloc(num_of_threads, sizeof(parssing_data*));// array to contain: functions params for each thread
	CheakAlocation(thread_params);
	HANDLE output_file = OpenFileWrap(p_params->output_path, CREATE_ALWAYS);
	CheakHandle(output_file);
	// set EOF at the end of the input file 
	SetFilePointerWrap(output_file, p_params->end_pos, FILE_BEGIN);

	BOOL retval= SetEndOfFile(output_file);
	if (!retval)
	{
		printf("error with set eof ,error code %d", GetLastError());
		exit(GetLastError());
	}
	CloseHandleWrap(output_file);

	int num_threads_to_add_more_line = num_of_lines % num_of_threads;
	uli lines_per_thread = (num_of_lines / num_of_threads);
	short add_one_more_line = 1;
	uli current_line_place = -1;//couse we start count from 0 the indexs 
	DWORD wait_code;

	for (int i = 0; i < num_of_threads; i++)
	{
		if ( i ==num_threads_to_add_more_line )
		{
			add_one_more_line = 0;
		}

		// params need to be allocate dynamiclly->init params 
		thread_params[i] = (parssing_data*)calloc(num_of_threads, sizeof(parssing_data)); // each cell in the array, contains params for thread
		CheakAlocation(thread_params[i]);
		if (i == 0)
		{thread_params[i]->start_pos = 0;}
		else	
			thread_params[i]->start_pos = end_of_lines[current_line_place] + 1;//one after the privous new line  

		current_line_place += add_one_more_line + lines_per_thread;
		thread_params[i]->end_pos = end_of_lines[current_line_place];
		thread_params[i]->output_path = p_params->output_path;
		thread_params[i]->input_path = p_params->input_path;
		thread_params[i]->key = p_params->key;
		p_thread_handles[i] = CreateThreadSimple(DecThread, (LPVOID) thread_params[i], &p_thread_ids[i]);
	}
	wait_code = WaitForMultipleObjects(num_of_threads, p_thread_handles, 1, TIMEOUT_IN_MILLISECONDS);
	FreeHandelsArray(p_thread_handles, num_of_threads);
	FreeArray(thread_params, num_of_threads);
	free(p_thread_ids);
	if (WAIT_OBJECT_0 != wait_code)
	{
		printf("Error when waiting for threads,Exiting program");
		exit(TIME_OUT_THREAD);
	}

}


static HANDLE CreateThreadSimple(LPTHREAD_START_ROUTINE p_start_routine,
		LPVOID p_thread_parameters,
		LPDWORD p_thread_id)
	{
		HANDLE thread_handle;

		if (NULL == p_start_routine)
		{
			printf("Error when creating a thread");
			printf("Received null pointer");
			exit(INVALID_INPUT_PARM_EMPTY_POINTER);
		}

		if (NULL == p_thread_id)
		{
			printf("Error when creating a thread");
			printf("Received null pointer");
			exit(INVALID_INPUT_PARM_EMPTY_POINTER);
		}

		thread_handle = CreateThread(
			NULL,                /*  default security attributes */
			0,                   /*  use default stack size */
			p_start_routine,     /*  thread function */
			p_thread_parameters, /*  argument to thread function */
			0,                   /*  use default creation flags */
			p_thread_id);        /*  returns the thread identifier */

		return thread_handle;
	}
