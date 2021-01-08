#include "websocketpp/client.hpp"
#include "websocketpp/config/asio_no_tls.hpp"
#include <map>
#include <memory>
#include <set>
#include <thread>
#include <vector>

class WebsocketClient {
  typedef websocketpp::client<websocketpp::config::asio> Client;

 private:
  std::string url_;
  Client      client_;

 public:
  WebsocketClient(const std::string url)
    : url_(url),
      client_() {
    std::cout<<"Init client\n";
    // 配置log
    // client_.set_access_channels(websocketpp::log::alevel::all);
    client_.clear_access_channels(websocketpp::log::alevel::all);
    client_.clear_error_channels(websocketpp::log::elevel::all);
    // init asio
    client_.init_asio();
    client_.start_perpetual();
    // Register our message handler
    client_.set_message_handler([this](websocketpp::connection_hdl hdl, Client::message_ptr msg) {
      std::cout << "server:" << msg->get_payload() << ", header:" << msg->get_header();
      Send(hdl, "I am client");
    });
  };

  int StartRunning() {
    std::error_code        ec;
    Client::connection_ptr con = client_.get_connection(url_, ec);
    if (ec) {
      std::cout << "could not create connection because: " << ec.message() << std::endl;
      return 0;
    }
    client_.connect(con);
    client_.run();
    return 1;
  };

  void StopRunning() {
    client_.stop();
  };

  void Send(websocketpp::connection_hdl hdl, const std::string& msg) {
    try {
      client_.send(hdl, msg, websocketpp::frame::opcode::binary);
    }
    catch (const websocketpp::exception& e) {
      std::cout << "Websocket send failed: " << e.what();
    }
    catch (...) {
      std::cout << "Websocket send failed: unknown exception";
    }
  };
};