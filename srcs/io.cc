#include "paging.hh"

void stdin_info(int *num_operate, int *num_process, int *N, int *M)
{
	scanf("%d %d %d %d", num_operate, num_process, N, M);
}

void stdin_operate(int *operate_id, int *pid, int *page)
{
	scanf("%d %d %d", operate_id, pid, page);
}

void stdout_memory(t_data *data)
{
	// print physical memory
	printf("%-30s", ">> Physical Memory (PID): ");
	for (int i=0;i<data->max_frames;i++){
		if (i%4==0) printf("|");
		if (data->phys->memory[i].pid == -1) printf("-");
		else printf("%d", data->phys->memory[i].pid);
	} if (data->max_frames%4 == 0) printf("|");
	printf("\n");

	printf("%-30s", ">> Physical Memory (AID): ");
	for (int i=0;i<data->max_frames;i++){
		if (i%4==0) printf("|");
		if (data->phys->memory[i].aid == -1) printf("-");
		else printf("%d", data->phys->memory[i].aid);
	} if (data->max_frames%4 == 0) printf("|");
	printf("\n");
	
	// print virtual memory
	for (int pid=0;pid<data->num_process;pid++){
		printf(">> PID(%d) %-20s", pid, "Page Table (AID): ");
		for (int i=0;i<data->max_pages;i++){
			if (i%4==0) printf("|");
			if ((data->virt+pid)->memory[i].aid == -1) printf("-");
			else printf("%d", (data->virt+pid)->memory[i].aid);
		} if (data->max_pages%4 == 0) printf("|");
		printf("\n");

		printf(">> PID(%d) %-20s", pid, "Page Table (Valid): ");
		for (int i=0;i<data->max_pages;i++){
			if (i%4==0) printf("|");
			if ((data->virt+pid)->memory[i].valid_bit == -1) printf("-");
			else printf("%d", (data->virt+pid)->memory[i].valid_bit);
		} if (data->max_pages%4 == 0) printf("|");
		printf("\n");

		printf(">> PID(%d) %-20s", pid, "Page Table (FI): ");
		for (int i=0;i<data->max_pages;i++){
			if (i%4==0) printf("|");
			if ((data->virt+pid)->memory[i].frame_idx == -1) printf("-");
			else printf("%d", (data->virt+pid)->memory[i].frame_idx);
		} if (data->max_pages%4 == 0) printf("|");
		printf("\n");
	}
	printf("\n");
}

void stdout_pagefault(int page_fault)
{
	printf("%d\n", page_fault);
}
