#include "websocketpp_demo_server.h"
#include <atomic>
#include <iostream>
#include <map>

int main() {
  uint16_t port=11234;
  WebsocketServer server_ = WebsocketServer(port);
  server_.StartRunning();
  while (true)
  {
    std::this_thread::sleep_for(std::chrono::seconds(2));
  }
  
  return 0;
}