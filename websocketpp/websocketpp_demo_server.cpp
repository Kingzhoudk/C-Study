#include "websocketpp_demo.h"
#include <atomic>
#include <iostream>
#include <map>

WebsocketServer::WebsocketServer(const uint16_t port)
  : port_(port),
    server_(),
    websocket_server_thread_() {
  std::cout << "Init Server\n";
  // 配置log
  // server_.set_access_channels(websocketpp::log::alevel::all);
  server_.clear_access_channels(websocketpp::log::alevel::all);
  // 设置多播地址？
  //server_.set_reuse_addr(true);
  // init asio
  server_.init_asio();
  server_.set_open_handler([this](websocketpp::connection_hdl hdl) {});
  server_.set_close_handler([this](websocketpp::connection_hdl hdl) {});
  // Register our message handler
  server_.set_message_handler([this](websocketpp::connection_hdl hdl, Server::message_ptr msg) {
    Send(hdl, "I am server");
  });
}

void WebsocketServer::StartRunning() {
  std::error_code ec;
  server_.listen(port_, ec);
  if (ec) {
    std::cout << "start websocketpp server failed: " << ec.message();
  }
  else {
    std::cout << "start websocketpp server\n";
    server_.start_accept();
    websocket_server_thread_ = std::thread([this] {
      server_.run();
    });
  }
}

void WebsocketServer::StopRunning() {
  server_.stop();
}

void WebsocketServer::Send(const websocketpp::connection_hdl& hl, const std::string& msg) {
  try {
    server_.send(hl, msg, websocketpp::frame::opcode::binary);
  }
  catch (const websocketpp::exception& e) {
    std::cout << "Websocket send failed: " << e.what();
  }
  catch (...) {
    std::cout << "Websocket send failed: unknown exception";
  }
}

int main(int argc, char** argv) {
  uint16_t port = 11234;
  WebsocketServer server_ = WebsocketServer(port);
  server_.StartRunning();
  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
  }

  return 0;
}