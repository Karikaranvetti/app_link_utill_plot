#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
 
typedef struct __attribute__ ((packed)) {
    uint32_t ts;
    uint16_t device_id;
    uint16_t app_id2;
    uint16_t app_id;
    uint16_t app_id1;
    uint64_t send_data;
    uint64_t recived_data;

    
}device_data;
 
 
  struct Message
{
  uint32_t one;
  uint64_t two;
  int arr[3];
};

typedef struct __attribute__ ((packed)) 
{
  uint16_t count : 13, r : 3;
}data_que_count;


typedef struct collector_data {
	device_data data;
	uint32_t priority;  // Lower values indicate higher priority
	struct collector_data* next;

} collector_data;

struct in_addr pub_port_list[UINT8_MAX];    //in_addr is a 32 bit ip address struct
uint32_t pub_port_list_len = 0;

device_data* data_que;
data_que_count data_count;
int flag=0;
collector_data* buffer_que1 =NULL;
collector_data* buffer_que2 =NULL;


 