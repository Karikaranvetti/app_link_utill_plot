//#pragma once
#include "zmq.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "data.h"

int main()
{
  int hwm = 2000;
  void *context = zmq_ctx_new();
  void *socket = zmq_socket(context, ZMQ_PUB);
  zmq_setsockopt(socket, ZMQ_SNDHWM, &hwm, sizeof(int));
  zmq_bind(socket, "tcp://*:8006");
  sleep(1);
  //  Initialize random number generator
  srandom((unsigned)time(NULL));

  while (1)
  {

    device_data data;
    data.device_id = 255;
    data.app_id = (rand() % (255 - 1 + 1)) + 1;
    data.recived_data = (rand() % (1024 - 1 + 1)) + 1;
    data.send_data = (rand() % (1024 - 1 + 1)) + 1;
    zmq_send(socket, &data, sizeof(data), 0);

    sleep(1);
  }

  // zmq_close(socket);
  // zmq_term(context);
}