#pragma once
#include "zmq.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>
#include "app_deff.h" 

collector_data* new_collector_data(device_data d)
{
	collector_data* temp = (collector_data*)malloc(sizeof(collector_data));
	temp->data = d;
	temp->priority = d.ts;
	temp->next = NULL;

	return temp;
}
 
int isCollectorEmpty(collector_data** head)
{
	return (*head) == NULL;
}
device_data peek_cdata(collector_data** head)
{
	return (*head)->data;
}

void pop_cdata(collector_data** head)
{
	collector_data* temp = *head;
	(*head) = (*head)->next;
	free(temp);
}

void push_cdata(collector_data** head, device_data d)
{
	collector_data* start = (*head);
	collector_data* temp = new_collector_data(d);
    if(isCollectorEmpty(head)){
        *head=temp;

    }else if ((*head)->priority > d.ts) {
		temp->next = *head;
		(*head) = temp;
	}
	else {
		while (start->next != NULL &&
			start->next->priority < d.ts) {
			start = start->next;
		}
		temp->next = start->next;
		start->next = temp;
	}
}


void data_process(){
    data_count.count=0;
	device_data data;
    while (true)
    {   
        
        flag=0; 
		while(!isCollectorEmpty(&buffer_que2)){
			data=peek_cdata(&buffer_que2);
			pop_cdata(&buffer_que2);
			data_que[data_count.count].app_id=data.app_id;
			data_que[data_count.count].device_id=data.device_id;
			data_que[data_count.count].recived_data=data.recived_data;
			data_que[data_count.count].send_data=data.send_data;
			data_que[data_count.count].ts=data.ts;
			// printf("The data time is :%d\nThe device id is :%d\nThe App id is :%d\nThe recive data is :%ld\nThe device send data is :%ld\nthe count1 %d and count2 %d\n",data.ts,data.device_id,data.app_id,data.recived_data,data.send_data,data_count.count,data_count[1].count);
			data_count.count++;
		}
        sleep(5);
        flag=1; 
		while(!isCollectorEmpty(&buffer_que1)){
			data=peek_cdata(&buffer_que1);
			pop_cdata(&buffer_que1);
			data_que[data_count.count].app_id=data.app_id;
			data_que[data_count.count].device_id=data.device_id;
			data_que[data_count.count].recived_data=data.recived_data;
			data_que[data_count.count].send_data=data.send_data;
			data_que[data_count.count].ts=data.ts;
			// printf("The data time is :%d\nThe device id is :%d\nThe App id is :%d\nThe recive data is :%ld\nThe device send data is :%ld\nthe count1 %d and count2 %d\n",data.ts,data.device_id,data.app_id,data.recived_data,data.send_data,data_count.count,data_count[1].count);
			data_count.count++;
		}

        sleep(5);
    }
    
}

