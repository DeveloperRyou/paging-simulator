#include "paging.hh"

void victim_fifo(t_data *data, int pid, int aid)
{
	// do nothing
	return;
}

void victim_stack(t_data *data, int pid, int aid)
{
	if (pid == -1 || aid == -1)
		return;
	for (int i=0;i<data->que->len;i++){
		if (data->que->array[i].pid == pid && data->que->array[i].aid == aid){
			// delay used memory
			t_queue_unit temp = data->que->array[i];
			for (int idx=i;idx<data->que->len - 1;idx++){
				data->que->array[idx] = data->que->array[idx + 1];
			}
			data->que->array[data->que->len - 1] = temp;
			break;
		}
	}
}

void vitcim_sampled_update(t_data *data)
{
	// update ref byte 
	for (int i=0;i<data->que->len;i++){
		data->que->array[i].refbyte = \
		(data->que->array[i].refbyte >> 1) | (128 * data->que->array[i].refbit);
		data->que->array[i].refbit = 0;
	}
}

void victim_sampled(t_data *data, int pid, int aid)
{
	// set ref bit
	for (int i=0;i<data->que->len;i++)
		if (data->que->array[i].pid == pid && data->que->array[i].aid == aid)
			data->que->array[i].refbit = 1;

	if (pid != -1 && aid != -1)
		return;
	// choose victim
	int idx = 0;
	int mn = 256;
	for (int i=0;i<data->que->len;i++){
		if (data->que->array[i].refbyte < mn){
			mn = data->que->array[i].refbyte;
			idx = i;
		}
	}
	t_queue_unit temp = data->que->array[idx];
	for (int i=idx;i>0;i--)
		data->que->array[i] = data->que->array[i-1];
	data->que->array[0] = temp;
}

void victim_secondchance(t_data *data, int pid, int aid)
{
	// set ref bit
	for (int i=0;i<data->que->len;i++)
		if (data->que->array[i].pid == pid && data->que->array[i].aid == aid)
			data->que->array[i].refbit = 1;

	if (pid != -1 && aid != -1)
		return;
	int idx = data->que->len;
	// find 0 refbit
	for (int i=0;i<data->que->len;i++){
		if (data->que->array[i].refbit == 0){
			idx = i;
			break;
		}
	}
	// delay(pushback) 1 refbit before first 0 refbit
	if (idx == 0) return;
	t_queue_unit *temp = new t_queue_unit[idx];
	for (int i=0;i<idx;i++){
		data->que->array[i].refbit = 0;
		temp[i] = data->que->array[i];
	}
	for (int i=0;i<data->que->len;i++){
		if (i < data->que->len - idx)
			data->que->array[i] = data->que->array[i + idx];
		else
			data->que->array[i] = temp[i + idx - data->que->len];
	}
}

void victim_lfu(t_data *data, int pid, int aid)
{
	for (int i=0;i<data->que->len;i++) // add used
		if (data->que->array[i].pid == pid && data->que->array[i].aid == aid)
			data->que->array[i].used++;

	if (pid != -1 && aid != -1)
		return;
	int idx = 0;
	int mn = 2147483467;
	for (int i=0;i<data->que->len;i++){
		// find least used and choose victim
		if (data->que->array[i].used < mn){
			mn = data->que->array[i].used;
			idx = i;
		}
	}
	t_queue_unit temp = data->que->array[idx];
	for (int i=idx;i>0;i--)
		data->que->array[i] = data->que->array[i-1];
	data->que->array[0] = temp;
}

void victim_mfu(t_data *data, int pid, int aid)
{
	for (int i=0;i<data->que->len;i++) // add used
		if (data->que->array[i].pid == pid && data->que->array[i].aid == aid)
			data->que->array[i].used++;

	if (pid != -1 && aid != -1)
		return;
	int idx = 0;
	int mx = -1;
	for (int i=0;i<data->que->len;i++){
		// find most used and choose victim
		if (data->que->array[i].used > mx){
			mx = data->que->array[i].used;
			idx = i;
		}
	}
	t_queue_unit temp = data->que->array[idx];
	for (int i=idx;i>0;i--)
		data->que->array[i] = data->que->array[i-1];
	data->que->array[0] = temp;
}

void victim_optimal(t_data *data, int pid, int aid)
{
	if (pid != -1 && aid != -1)
		return;
	int idx = 0;
	for (int i=data->max_operate-1;i>data->current_operate;i--){
		if (data->operate[i].operate_id == 1){
			pid = data->operate[i].pid;
			aid = data->operate[i].page;
			for (int idx=0;idx<data->que->len;idx++){
				// if memory used, move end of que
				// next used memory will move to end - 1
				if (data->que->array[idx].pid == pid && data->que->array[idx].aid == aid){
					t_queue_unit temp = data->que->array[idx];
					for (int j=idx;j<data->que->len - 1;j++)
						data->que->array[j] = data->que->array[j+1];
					data->que->array[data->que->len - 1] = temp;
					break;
				}
			}
		}
	}
}
