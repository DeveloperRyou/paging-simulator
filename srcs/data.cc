#include "paging.hh"

t_data *make_data(int num_process, int N, int M, int num_operate, int option)
{
	t_data *data;

	// allocate memory
	// physical
	data = new t_data;
	data->phys = new t_physical;
	data->phys->memory = new t_physical_unit[M];
	for (int i=0;i<M;i++){
		data->phys->memory[i].aid = -1;
		data->phys->memory[i].pid = -1;
	}
	// virtual
	data->virt = new t_virtual[num_process];
	for (int pid=0;pid<num_process;pid++){
		(data->virt+pid)->memory = new t_virtual_unit[N];
		for (int i=0;i<N;i++){
			(data->virt+pid)->memory[i].aid = -1;
			(data->virt+pid)->memory[i].frame_idx = -1;
			(data->virt+pid)->memory[i].valid_bit = -1;
		}
		(data->virt+pid)->max_aid = 0;
	}
	// victim queue
	data->que = new t_queue;
	data->que->array = new t_queue_unit[M + 1]; // prevent segfault
	for (int i=0;i<M+1;i++){
		data->que->array[i].aid = -1;
		data->que->array[i].pid = -1;
		data->que->array[i].refbit = 0;
		data->que->array[i].refbyte = 255;
		data->que->array[i].used = 0;
	}
	data->que->len = 0;
	data->que->timeinterval = 0;
	// operate
	data->operate = new t_operate[num_operate];
	for (int i=0;i<num_operate;i++){
		data->operate[i].operate_id = 0;
		data->operate[i].page = 0;
		data->operate[i].pid = 0;
	}
	data->max_operate = num_operate;
	data->current_operate = 0;
	// init datas
	data->num_process = num_process;
	data->max_pages = N;
	data->max_frames = M;
	data->page_fault = 0;
	// set victim algorithm
	if (option == 1)
		data->victim = &victim_fifo;
	else if (option == 2)
		data->victim = &victim_stack;
	else if (option == 3)
		data->victim = &victim_sampled;
	else if (option == 4)
		data->victim = &victim_secondchance;
	else if (option == 5)
		data->victim = &victim_lfu;
	else if (option == 6)
		data->victim = &victim_mfu;
	else if (option == 7)
		data->victim = &victim_optimal;
	return data;
}

void free_data(t_data *data)
{
	// free data
	// physical
	delete data->phys->memory;
	delete data->phys;
	// virtual
	for (int i=0;i<data->num_process;i++){
		delete (data->virt+i)->memory;
	} 
	delete data->virt;
	// queue
	delete data->que->array;
	delete data->que;
	// operate
	delete data->operate;
	// free data
	delete data;
}