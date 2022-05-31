#include "paging.hh"

int main(int argc, char **argv)
{
	// run with option -page=""
	if (argc == 2)
	{
		int option = parse_option(argv[1]);
		if (option == 0) // invalid option
			return 0;
		// input informations
		int num_operate, num_process, N, M;
		stdin_info(&num_operate, &num_process, &N, &M);

		// make physical, virtual memory
		t_data *data = make_data(num_process, N/32, M/32, num_operate, option);
		
		// input all operate
		for (int i=0;i<num_operate;i++)
		{
			// input each operation
			int operate_id, pid, page;
			stdin_operate(&operate_id, &pid, &page);
			data->operate[i].operate_id = operate_id;
			data->operate[i].pid = pid;
			data->operate[i].page = page;
		}

		for (int i=0;i<num_operate;i++)
		{
			// load operate
			int operate_id, pid, page;
			operate_id = data->operate[i].operate_id;
			pid = data->operate[i].pid;
			page = data->operate[i].page;
			data->current_operate = i;
			// do operate
			operate(data, operate_id, pid, page);
			// print memory
			stdout_memory(data);
		}
		stdout_pagefault(data->page_fault);
		free_data(data);
	}
	return 0;
}
