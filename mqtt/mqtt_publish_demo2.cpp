#include <iostream>
#include <mosquitto.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <unistd.h>

#define HOST "127.0.0.1"
#define PORT 1883
#define KEEP_ALIVE 60
#define MSG_MAX_SIZE 512

bool session = true;

void my_connect_callback(struct mosquitto* mosq, void* userdata, int result) {
  if (!result) {
    printf("Connect succeed\n");
  }
  else {
    fprintf(stderr, "Connect failed\n");
  }
}

void my_disconnect_callback(struct mosquitto* mosq, void* userdata, int result) {
  printf("Connect failed\n");
}

int main() {
  char buff[MSG_MAX_SIZE];
  mosquitto* mosq = NULL;
  //libmosquitto 库初始化
  mosquitto_lib_init();
  //创建mosquitto客户端
  mosq = mosquitto_new(NULL, session, NULL);
  if (!mosq) {
    printf("create client failed..\n");
    mosquitto_lib_cleanup();
    return 1;
  }
  if (mosquitto_username_pw_set(mosq, "compass", "compass")) {
    std::cout << "failed";
  }
  //连接服务器
  if (mosquitto_connect(mosq, HOST, PORT, KEEP_ALIVE)) {
    fprintf(stderr, "Unable to connect.\n");
    return 1;
  }

  mosquitto_connect_callback_set(mosq, my_connect_callback);
  mosquitto_disconnect_callback_set(mosq, my_disconnect_callback);
  //开启一个线程，在线程里不停的调用 mosquitto_loop() 来处理网络信息
  int loop = mosquitto_loop_start(mosq);
  if (loop != MOSQ_ERR_SUCCESS) {
    printf("mosquitto loop error\n");
    return 1;
  }
  double lat = 3407895.0;
  double lon = 1003735.0;
  double theta = 0;
  while (true) {
    /*发布消息*/
    lat = lat + 1;
    lon++;
    theta++;
    std::string msg = "{\"params\": {\"location\": {\"lat\": " + std::to_string(lat)
                      + ",\"lon\":" + std::to_string(lon)
                      + ",\"theta\":" + std::to_string(theta)
                      + "},\"speed\": 10,\"flight_size\":{\"length\": 10,\"width\": 5}},\"channel\": \"flight_tracking\",\"flight\": \"flight1\",\"timestamp\": 1609993953.29184}";
    std::cout << "send:" << msg << "\n";
    mosquitto_publish(mosq, NULL, "test", strlen(msg.c_str()) + 1, msg.c_str(), 0, 0);
    memset(buff, 0, sizeof(buff));
    sleep(1);
  }
  mosquitto_destroy(mosq);
  mosquitto_lib_cleanup();
  return 0;
}