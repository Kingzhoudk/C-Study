#include <mosquitto.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread>

#define HOST "localhost"
#define PORT 1883
#define KEEP_ALIVE 60
#define MSG_MAX_SIZE 512

bool session = true;

void my_connect_callback(struct mosquitto* mosq, void* userdata, int result) {
  int i;
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
  while (fgets(buff, MSG_MAX_SIZE, stdin) != NULL) {
    /*发布消息*/
    mosquitto_publish(mosq, NULL, "Test", strlen(buff) + 1, buff, 0, 0);
    memset(buff, 0, sizeof(buff));
  }
  mosquitto_destroy(mosq);
  mosquitto_lib_cleanup();
  return 0;
}