#include "paging.hh"

void virtual_malloc(t_virtual *virt, int pages, int max_pages)
{
	int st = 0;
	int ed = 0;
	// find empty place
	while (ed - st < pages && ed < max_pages){
		if (virt->memory[ed].aid != -1)
			st = ed+1;
		ed++;
	}
	// allocate
	if (ed - st == pages){
		for (int i=st;i<ed;i++){
			virt->memory[i].aid = virt->max_aid;
			virt->memory[i].valid_bit = 0;
		}
		virt->max_aid++;
	}
}

int buddy(int pages)
{
	int len=1;
	while (pages>len)
		len *= 2;
	return len;
}

int physical_allocate(t_data *data, int pid, int aid)
{
	// allocate with buddy system
	int pages = 0;
	// find page length
	for (int i=0;i<data->max_pages;i++)
		if ((data->virt+pid)->memory[i].aid == aid)
			pages++;
	// make length to 2^n (buddy system)
	pages = buddy(pages);
	int len = 0;
	int mn_len = 2147483647;
	int st = 0;
	int ed = 0;
	int st_idx = 0;
	int ed_idx = 0;
	// find smallest empty place
	while (ed_idx < data->max_frames){
		if (st_idx != ed_idx && (ed_idx - st_idx) % pages == 0)
			len++;
		if (data->phys->memory[ed_idx].aid != -1){
			if (0 < len && len < mn_len){
				mn_len = len;
				st = st_idx;
				ed = st + pages;
			}
			st_idx += pages * (0 < len ? len : 1);
			ed_idx = st_idx;
			len = 0;
		}
		else
			ed_idx++;
	}
	if (st_idx != ed_idx && (ed_idx - st_idx) % pages == 0)
		len++;
	if (len != 0 && len < mn_len){
		mn_len = len;
		st = st_idx;
		ed = st + pages;
	}
	// allocate success
	if (ed - st == pages){
		for (int i=st;i<ed;i++){
			data->phys->memory[i].pid = pid;
			data->phys->memory[i].aid = aid;
		}
		for (int i=0;i<data->max_pages;i++){
			if ((data->virt+pid)->memory[i].aid == aid){
				(data->virt+pid)->memory[i].frame_idx = st;
				(data->virt+pid)->memory[i].valid_bit = 1;
			}
		}
		return 0;
	}
	// allocate fail
	return 1;
}

void virtual_free(t_virtual *virt, int aid, int max_pages)
{
	// find allocated place and free
	for (int i=0;i<max_pages;i++){
		if (virt->memory[i].aid == aid){
			virt->memory[i].aid = -1;
			virt->memory[i].frame_idx = -1;
			virt->memory[i].valid_bit = -1;
		}
	}
}

void physical_free(t_data *data, int pid, int aid)
{
	// find allocated place and free
	for (int i=0;i<data->max_frames;i++){
		if (data->phys->memory[i].pid == pid && data->phys->memory[i].aid == aid){
			data->phys->memory[i].aid = -1;
			data->phys->memory[i].pid = -1;
		}
	}
	// find allocated virtual place and reset valid and idx
	for (int i=0;i<data->max_pages;i++){
		if ((data->virt+pid)->memory[i].aid == aid){
			(data->virt+pid)->memory[i].frame_idx = -1;
			(data->virt+pid)->memory[i].valid_bit = -1;
		}
	}
}

int is_pagefault(t_physical *phys, int pid, int aid, int max_frames)
{
	// find memory
	for (int i=0;i<max_frames;i++)
		if (phys->memory[i].pid == pid && phys->memory[i].aid == aid)
			return 0;
	return 1;
}