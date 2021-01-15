#include "mqtt/MQTTClient.h"
#include <cstdint>
#include <string>

struct MqttData {
  uint32_t id;
  double x;
  double y;
  double theta;
};

class MqttPublish {
 public:
  MqttData mqtt_data_;
  MqttPublish(const std::string address, const int id, const int time_out)
    : address_(address),
      client_id_(id),
      time_out_(time_out){
  };

 private:
  MQTTClient client_;
  std::string address_;
  int client_id_;
  int time_out_;
};

class MqttSubscribe {
 public:
  MqttData mqtt_data_;
  MqttSubscribe(const std::string address, const int id, const int time_out);

 private:
  MQTTClient client_;
  std::string address_;
  int client_id_;
  int time_out_;
};