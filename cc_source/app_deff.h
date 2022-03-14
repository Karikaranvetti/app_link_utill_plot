#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
#include <inttypes.h>



typedef struct __attribute__ ((packed)) {
    uint8_t device_id;
    uint32_t ts;
    uint16_t app_id;
    uint64_t send_data;
    uint64_t recived_data;

    
}device_data;
 
 
  struct Message
{
  uint32_t one;
  uint64_t two;
  int arr[3];
};

// typedef struct Pub_device_addr{
//   string ip_addr;
//   uint32_t port;
//   uint8_t device_id;

// } Pub_device_addr;


struct in_addr pub_port_list[UINT8_MAX];    //in_addr is a 32 bit ip address struct
uint32_t pub_port_list_len = 0;

device_data* data_que[200];
device_data* data_que2[200];
int flag=0;
int data_que_count1=0;
int data_que_count2=0;

 