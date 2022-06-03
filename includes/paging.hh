#ifndef PAGING_H
# define PAGING_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <queue>

using namespace std;

// struct for memory
typedef struct s_physical_unit
{
	int pid;
	int aid;
} t_physical_unit;

typedef struct s_virtual_unit
{
	int aid;
	int valid_bit;
	int frame_idx;
} t_virtual_unit;

typedef struct s_physical
{
	t_physical_unit *memory;
} t_physical;

typedef struct s_virtual
{
	t_virtual_unit *memory;
	int max_aid;
} t_virtual;


typedef struct s_queue_unit
{
	int pid;
	int aid;
	unsigned char refbit;
	unsigned char refbyte;
	int used;
} t_queue_unit;

typedef struct s_queue
{
	t_queue_unit *array;
	int len;
} t_queue;

typedef struct s_operate
{
	int operate_id;
	int pid;
	int page;
} t_operate;

typedef struct s_data {
	t_physical *phys;
	t_virtual *virt;
	t_operate *operate;
	int num_process;
	int max_pages;
	int max_frames;
	int page_fault;
	int option;
	void (*victim)(struct s_data *data, int pid, int aid);
	t_queue *que;
	int max_operate;
	int current_operate;
} t_data;

// parse.cc
int parse_option(char *str);

// data.cc
t_data *make_data(int num_process, int N, int M, int num_operate, int option);
void free_data(t_data *data);

// memory.cc
void virtual_malloc(t_virtual *virt, int pages, int max_pages);
int physical_allocate(t_data *data, int pid, int aid);
void virtual_free(t_virtual *virt, int aid, int max_pages);
void physical_free(t_data *data, int pid, int aid);
int is_pagefault(t_physical *phys, int pid, int aid, int max_frames);

// io.cc
void stdin_info(int *num_operate, int *num_process, int *N, int *M);
void stdin_operate(int *operate_id, int *pid, int *page);
void stdout_memory(t_data *data);
void stdout_pagefault(int page_fault);

// operate.cc
void operate(t_data *data, int operate_id, int pid, int page);

// queue.cc
void queue_pop(t_data *data);
void queue_push(t_data *data, int pid, int aid);
void queue_delete(t_data *data, int pid, int aid);

// victim.cc
void victim_fifo(t_data *data, int pid, int aid);
void victim_stack(t_data *data, int pid, int aid);
void vitcim_sampled_update(t_data *data);
void victim_sampled(t_data *data, int pid, int aid);
void victim_secondchance(t_data *data, int pid, int aid);
void victim_lfu(t_data *data, int pid, int aid);
void victim_mfu(t_data *data, int pid, int aid);
void victim_optimal(t_data *data, int pid, int aid);

#endif