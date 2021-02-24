#include "websocketpp_demo.h"
#include <atomic>
#include <iostream>
#include <map>

WebsocketClient::WebsocketClient(const std::string url)
  : url_(url),
    client_(),
    websocket_client_thread_() {
  std::cout << "Init client\n";
  // 配置log
  // client_.set_access_channels(websocketpp::log::alevel::all);
  client_.clear_access_channels(websocketpp::log::alevel::all);
  client_.clear_error_channels(websocketpp::log::elevel::all);
  // init asio
  client_.init_asio();
  client_.start_perpetual();
  // Register our message handler
  client_.set_message_handler([this](websocketpp::connection_hdl hdl, Client::message_ptr msg) {
    std::cout << "Rcv: " << msg->get_payload() << "\n";
  });
}

void WebsocketClient::StartRunning() {
  std::error_code ec;
  Client::connection_ptr con = client_.get_connection(url_, ec);
  server_hdl_ = con->get_handle();
  if (ec) {
    std::cout << "could not create connection because: " << ec.message() << std::endl;
  }
  else {
    client_.connect(con);
    websocket_client_thread_ = std::thread([this] {
      client_.run();
    });
  }
}

void WebsocketClient::StopRunning() {
  client_.stop();
}

void WebsocketClient::Send(const std::string& msg) {
  try {
    client_.send(server_hdl_, msg, websocketpp::frame::opcode::binary);
  }
  catch (const websocketpp::exception& e) {
    std::cout << "Websocket send failed: " << e.what();
  }
  catch (...) {
    std::cout << "Websocket send failed: unknown exception";
  }
}

int main(int argc, char** argv) {
  std::string uri = "ws://localhost:11234";
  WebsocketClient client_ = WebsocketClient(uri);
  client_.StartRunning();
  while (true) {
    std::cout << "Send: I am client\n";
    client_.Send("I am client");
    std::this_thread::sleep_for(std::chrono::seconds(2));
  }

  return 0;
}