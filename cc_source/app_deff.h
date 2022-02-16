#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
