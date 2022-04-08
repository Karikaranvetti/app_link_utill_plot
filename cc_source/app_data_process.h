#pragma once
#include "zmq.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>
#include "app_deff.h" 

void enqueue(device_data value,device_data* que ,uint16_t* size){
	que[*size] = value;
	*size=*size+1;   
}
device_data dequeue(device_data* que ,uint16_t *size){
    int ind=0;
    for (int i = 0; i <= *size; i++) {
 
        if (highestPriority> que[i].ts) {
            highestPriority = que[i].ts;
            ind = i;
        }
    }
    device_data temp =que[ind];
    for (int i = ind; i < *size; i++) {
         que[i] = que[i + 1];
     }
    *size=*size-1;
    return temp;
}
void data_process(){
    data_count.count=0;      
    while (true){
        flag=0; 
		while(buffer_que1_count != 0){
			 
            device_data data=dequeue(buffer_que1,&buffer_que1_count);
			data_que[data_count.count].app_id=data.app_id;
			data_que[data_count.count].device_id=data.device_id;
			data_que[data_count.count].recived_data=data.recived_data;
			data_que[data_count.count].send_data=data.send_data;
			data_que[data_count.count].ts=data.ts;
 			if (data.ts){
                data_count.count++;
            }
		}
        sleep(5);
        flag=1; 
		while(buffer_que2_count != 0 ){
            device_data data=dequeue(buffer_que2,&buffer_que2_count);
			data_que[data_count.count].app_id=data.app_id;
			data_que[data_count.count].device_id=data.device_id;
			data_que[data_count.count].recived_data=data.recived_data;
			data_que[data_count.count].send_data=data.send_data;
			data_que[data_count.count].ts=data.ts;
            if (data.ts){
                data_count.count++;
            }

		}

        sleep(5);
    }
    
}

