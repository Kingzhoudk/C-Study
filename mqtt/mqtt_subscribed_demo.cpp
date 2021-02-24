#include <mosquitto.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HOST "localhost"
#define PORT 1883
#define KEEP_ALIVE 60

bool session = true;

void my_message_callback(struct mosquitto* mosq, void* userdata, const struct mosquitto_message* message) {
  // 收到消息，打印
  if (message->payloadlen) {
    printf("%s : %s", message->topic, message->payload);
  }
  else {
    printf("%s (null)\n", message->topic);
  }
  fflush(stdout);
}

void my_connect_callback(struct mosquitto* mosq, void* userdata, int result) {
  int i;
  if (!result) {
    // 连接成功，开启订阅
    printf("Connect succeed\n");
    mosquitto_subscribe(mosq, NULL, "test", 2);
  }
  else {
    fprintf(stderr, "Connect failed\n");
  }
}

void my_subscribe_callback(struct mosquitto* mosq, void* userdata, int mid, int qos_count, const int* granted_qos) {
  int i;
  printf("Subscribed (mid: %d): %d", mid, granted_qos[0]);
  for (i = 1; i < qos_count; i++) {
    printf(", %d", granted_qos[i]);
  }
  printf("\n");
}

void my_log_callback(struct mosquitto* mosq, void* userdata, int level, const char* str) {
  /* Pring all log messages regardless of level. */
  printf("%s\n", str);
}

int main() {
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
  //设置回调函数，需要时可使用
  //mosquitto_log_callback_set(mosq, my_log_callback);
  mosquitto_connect_callback_set(mosq, my_connect_callback);
  mosquitto_message_callback_set(mosq, my_message_callback);
  //mosquitto_subscribe_callback_set(mosq, my_subscribe_callback);
  //客户端连接服务器
  if (mosquitto_connect(mosq, HOST, PORT, KEEP_ALIVE)) {
    fprintf(stderr, "Unable to connect.\n");
    return 1;
  }
  //循环处理网络消息
  //It handles reconnecting in case server connection is lost.
  //掉线后重新会重新连接
  mosquitto_loop_forever(mosq, -1, 1);

  mosquitto_destroy(mosq);
  mosquitto_lib_cleanup();

  return 0;
}
