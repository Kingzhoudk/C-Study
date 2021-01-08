#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"
#include <atomic>
#include <iostream>

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// 取别名
typedef websocketpp::server<websocketpp::config::asio> websocket_server;
// pull out the type of messages sent by our config
typedef websocket_server::message_ptr message_ptr;

class WebsocketServer {
  WebsocketServer(){
    
  }

  // Define a callback to handle incoming messages
  void on_message(websocket_server* s, websocketpp::connection_hdl hdl, message_ptr msg) {
    if (msg->get_payload() == "stop-listening") {
        s->stop_listening();
        return;
    }

    try {
        s->send(hdl, msg->get_payload(), msg->get_opcode());
    } catch (websocketpp::exception const & e) {
        std::cout << "Echo failed because: "
                  << "(" << e.what() << ")" << std::endl;
    }
  };
};

int main() {
  return 0;
}