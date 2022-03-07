#pragma once
#include "zmq.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>
#include "app_deff.h"


void app_plot_config_init_connector_sub() {

  int len = 0;
  char rem_url[64];
  void *context = zmq_ctx_new();
  void *socket = zmq_socket(context, ZMQ_SUB);
   zmq_setsockopt(socket, ZMQ_SUBSCRIBE, "", 0);
  zmq_connect(socket, "tcp://127.0.0.1:8007");
  printf("subcriber Init ");

    for (uint32_t rmt_icnt = 0; rmt_icnt < pub_port_list_len; rmt_icnt++) {
        len = sprintf(rem_url, "%s%s%s", (char*) "tcp://", inet_ntoa(pub_port_list[rmt_icnt]), (char*) ":8007");
        rem_url[len] = '\0';
        printf(  "APP_PLOT :: PUB IP :::Subscribed to %s"   "\n", rem_url);
        zmq_connect(socket, rem_url);
    }
 

  while(1) {
    char buf [256];
    zmq_recv (socket, buf, 256, 0);
    device_data* data;
    zmq_msg_t in_msg;
    zmq_msg_init(&in_msg);
    zmq_recv(socket, &in_msg,sizeof(in_msg), 0);
    data = (device_data*)(&in_msg);
    printf("The device id is :%d\nThe App id is :%d\nThe recive data is :%ld\nThe device send data is :%ld\n\n",data->device_id,data->app_id,data->recived_data,data->send_data);
    sleep(1);
  }
zmq_close(socket);
zmq_term(context);
 
}