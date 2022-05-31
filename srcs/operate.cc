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
		int flag = 1;
		// check pagefault
		if (is_pagefault(data->phys, pid, page, data->max_frames)){
			data->page_fault++;
			// physical memory allocate with buddy system
			while (physical_allocate(data, pid, page)){
				// cannot allocate then remove victim
				if (data->que->len == 0){
					// cannot allocate (over size)
					flag = 0;
					break;
				}
				queue_pop(data);
				// reset(find) victim
				data->victim(data, -1, -1);
			}
			if (flag) queue_push(data, pid, page);
		}
		if (flag) data->victim(data, pid, page);
	}
	// virtual memory free
	else if (operate_id == 2){
		virtual_free(data->virt+pid, page, data->max_pages);
		physical_free(data, pid, page);
		queue_delete(data, pid, page);
	}
}