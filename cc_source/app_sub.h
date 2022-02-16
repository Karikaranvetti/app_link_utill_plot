#pragma once
#include "zmq.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>
#include "app_deff.h"


void app_plot_config_init_connector_sub() {
  void *context = zmq_ctx_new();
  void *socket = zmq_socket(context, ZMQ_SUB);
  zmq_connect(socket, "tcp://127.0.0.1:5553");
  zmq_setsockopt(socket, ZMQ_SUBSCRIBE, "", 0);

  while(1) {
     
    device_data* data;
    zmq_msg_t in_msg;
    zmq_msg_init(&in_msg);
    zmq_recv(socket, &in_msg,sizeof(in_msg), 0);
    data = (device_data*)(&in_msg);
    printf("The device id is :%d\nThe App id is :%d\nThe recive data is :%ld\nThe device send data is :%ld\n\n",data->device_id,data->app_id,data->recived_data,data->send_data);
    sleep(1);
  }
//   zmq_close(socket);
//   zmq_term(context);
 
}