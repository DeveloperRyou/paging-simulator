#include "paging.hh"

void queue_pop(t_data *data)
{
	// pop index 0 and resize
	t_queue_unit victim = data->que->array[0];
	for (int i=0;i<data->que->len;i++)
		data->que->array[i] = data->que->array[i+1];
	data->que->len--;
	//debug : 
	printf("%d, %d poped\n", victim.pid, victim.aid);
	physical_free(data, victim.pid, victim.aid);
}

void queue_push(t_data *data, int pid, int aid)
{
	// push end of que
	data->que->array[data->que->len].pid = pid;
	data->que->array[data->que->len].aid = aid;
	//debug : 
	printf("idx : %d : %d, %d pushed\n", data->que->len, pid, aid);
	data->que->len++;
}

void queue_delete(t_data *data, int pid, int aid)
{
	// find frame and delete if it exist
	int flag = 0;
	for (int i=0;i<data->que->len;i++){
		if (data->que->array[i].pid == pid && data->que->array[i].aid == aid)
			flag = 1;
		if (flag)
			data->que->array[i] = data->que->array[i+1];
	}
	if (flag)
		data->que->len--;
}