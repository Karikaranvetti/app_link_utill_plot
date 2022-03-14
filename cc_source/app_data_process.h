#pragma once
#include "zmq.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>
#include "app_deff.h"


void data_process(){
    while (true)
    {   
        data_que_count1=0;
        flag=0; 
        sleep(10);
        data_que_count2=0;
        flag=1; 
        sleep(10);
    }
    
}