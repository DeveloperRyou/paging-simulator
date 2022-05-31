#include "paging.hh"

void operate(t_data *data, int operate_id, int pid, int page)
{
	// handle invalid input
	if (pid >= data->num_process) return;
	// virtual memory allocate
	if (operate_id == 0){
		virtual_malloc(data->virt+pid, page, data->max_pages);
	}
	// access page
	else if (operate_id == 1){
		// check pagefault
		if (is_pagefault(data->phys, pid, page, data->max_frames)){
			data->page_fault++;
			// physical memory allocate with buddy system
			while (physical_allocate(data, pid, page)){
				// cannot allocate then remove victim
				queue_pop(data);
				// reset(find) victim
				data->victim(data, -1, -1);
			}
			queue_push(data, pid, page);
		}
		data->victim(data, pid, page);
	}
	// virtual memory free
	else if (operate_id == 2){
		virtual_free(data->virt+pid, page, data->max_pages);
		physical_free(data, pid, page);
		queue_delete(data, pid, page);
	}
}