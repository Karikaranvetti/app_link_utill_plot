#pragma once
#include "zmq.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mutex>
#include <string.h>
#include <time.h>
#include "app_deff.h"

std::mutex myMutex;
device_data create_app_data(uint8_t device_id){
  device_data data;
  //  Initialize random number generator
  srandom ((unsigned) time (NULL));
  data.device_id=device_id;
  data.app_id=(rand() % (255 - 1 + 1)) + 1;
  data.recived_data=(rand() % (1024 - 1 + 1)) + 1;
  data.send_data=(rand() % (1024 - 1 + 1)) + 1;
  return data;

}

void pub_topic_send(void* socket ,char* word){
  while(1) {
    device_data data;
    char* topic =word;
    data=create_app_data(2);
    std::lock_guard<std::mutex> guard(myMutex);
    zmq_send (socket, topic,strlen(topic), ZMQ_SNDMORE);
    zmq_send(socket, &data,sizeof (data), 0);
 
  }
  zmq_close(socket);
 
}

void* app_device_config_init_connector_pub() {
  int hwm = 2000;
  void *context = zmq_ctx_new();
  void *socket = zmq_socket(context, ZMQ_PUB);
  zmq_setsockopt(socket, ZMQ_SNDHWM, &hwm, sizeof (int));
  zmq_bind(socket, "tcp://*:5563");
  printf("Pubilisher Init ");
  sleep(1);
   

return socket;
  
}

 