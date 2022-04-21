#pragma once
#include "zmq.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>
#include "app_deff.h"
 

void enqueue(device_data value, Buffer_que* que,int status,uint16_t* wp)
{  
    if(status==0){
        que[value.device_id].Buffer[Buffer_que1_count[value.device_id]] = value;
        //  printf("here %d oo\n",que[value.device_id].Buffer[Buffer_que1_count[value.device_id]].ts);
        if(Buffer_que1_count[value.device_id]==8191){
            Buffer_que1_count[value.device_id]=0;
        }
        else{
            Buffer_que1_count[value.device_id]++;
        }
        
    }else if(status==1){
        que[value.device_id].Buffer[Buffer_que2_count[value.device_id]] = value;
        // printf("here %d ppp \n",que[value.device_id].Buffer[Buffer_que2_count[value.device_id]].ts);
        if(Buffer_que2_count[value.device_id]==8191){
            Buffer_que2_count[value.device_id]=0;
        }
        else{
            Buffer_que2_count[value.device_id]++;
        }
    }  
    *wp=*wp+1; 
}



device_data dequeue1(Buffer_que* que, uint16_t* read_count){

    int index=0;
    uint32_t highestPriority = time(NULL) + 6;
    for (int i = 0; i < 8; i++)
    {
        
        if (highestPriority > que[i].Buffer[read_count[i]].ts && que[i].Buffer[read_count[i]].ts )
        {
            highestPriority = que[i].Buffer[read_count[i]].ts;
            index = i;
        }
    }
    device_data data =que[index].Buffer[read_count[index]];
    read_count[index]=read_count[index]+1;
    if(read_count[index]==8192){
        read_count[index]=0;
    }
    return data ;


}



void data_process()
{
    data_count.count = 0;
    while (true)
    {
        flag = 1;
        
        while (rp_count1!=wp_count1)
        {
            // printf("here %d sss \n",Buffer_que1[1].Buffer[read_count1[1]].ts);
            device_data data = dequeue1(Buffer_que1, read_count1);
            data_que[data_count.count].app_id = data.app_id;
            data_que[data_count.count].device_id = data.device_id;
            data_que[data_count.count].recived_data = data.recived_data;
            data_que[data_count.count].send_data = data.send_data;
            data_que[data_count.count].ts = data.ts;
        //  printf("!!!The data time is :%d\nThe device id is :%d\nThe App id is :%d\nThe recive data is :%ld\nThe device send data is :%ld\nthe count1 %d and read count %d  \n\n",data.ts,data.device_id,data.app_id,data.recived_data,data.send_data,data_count.count,read_count1[data.device_id]);

            if (data.ts)
            {
                data_count.count++;
            }
            rp_count1++;


        }
        sleep(5);
        flag = 0;
       
        while (rp_count2!=wp_count2)
        {
            device_data data = dequeue1(Buffer_que2, read_count2);
            data_que[data_count.count].app_id = data.app_id;
            data_que[data_count.count].device_id = data.device_id;
            data_que[data_count.count].recived_data = data.recived_data;
            data_que[data_count.count].send_data = data.send_data;
            data_que[data_count.count].ts = data.ts;
            // printf("****The data time is :%d\nThe device id is :%d\nThe App id is :%d\nThe recive data is :%ld\nThe device send data is :%ld\nthe count1 %d and read count %d  \n\n",data.ts,data.device_id,data.app_id,data.recived_data,data.send_data,data_count.count,read_count2[data.device_id]);

            if (data.ts  )
            {
                data_count.count++;
            }
            rp_count2++;
        }

        sleep(5);
    }
}



 