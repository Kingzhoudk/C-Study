#include "websocketpp_demo_client.h"
#include <atomic>
#include <iostream>
#include <map>

int main() {
  std::string uri="ws://localhost:11234";
  WebsocketClient client_ = WebsocketClient(uri);
  client_.StartRunning();
  while (true)
  {
    std::this_thread::sleep_for(std::chrono::seconds(2));
  }
  
  return 0;
}