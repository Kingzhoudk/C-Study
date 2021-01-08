#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"
#include <map>
#include <memory>
#include <set>
#include <thread>
#include <vector>

class WebsocketServer {
  // typedef取个别样好记的名字
  typedef websocketpp::server<websocketpp::config::asio>                                      Server;
  typedef std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>> ClientList;

 private:
  uint16_t   port_;
  Server     server_;
  ClientList client_list_;

 public:
  WebsocketServer(uint16_t port)
    : port_(port),
      server_(),
      client_list_() {
    std::cout << "Init server\n";
    // 配置log
    // server_.set_access_channels(websocketpp::log::alevel::all);
    server_.clear_access_channels(websocketpp::log::alevel::all);
    // 设置多播地址？
    server_.set_reuse_addr(true);
    // init asio
    server_.init_asio();
    server_.set_open_handler([this](websocketpp::connection_hdl hdl) {});
    server_.set_close_handler([this](websocketpp::connection_hdl hdl) {});
    // Register our message handler
    server_.set_message_handler([this](websocketpp::connection_hdl hdl, Server::message_ptr msg) {
      client_list_.insert(hdl);
      std::cout << "client:" << msg->get_payload() << ", header:" << msg->get_header();
      BroadcastClient("I am server");
    });
  };

  void StartRunning() {
    std::error_code ec;
    server_.listen(port_, ec);
    if (ec) {
      std::cout << "start websocketpp server failed: " << ec.message();
    }
    else {
      server_.start_accept();
      server_.run();
    }
  };
  void StopRunning() {
    server_.stop();
    client_list_.clear();
  };

  void BroadcastClient(const std::string& msg) {
    for (auto hdl : client_list_) {
      Send(hdl, msg);
    }
  };

  void Send(websocketpp::connection_hdl hdl, const std::string& msg) {
    try {
      server_.send(hdl, msg, websocketpp::frame::opcode::binary);
    }
    catch (const websocketpp::exception& e) {
      std::cout << "Websocket send failed: " << e.what();
    }
    catch (...) {
      std::cout << "Websocket send failed: unknown exception";
    }
  };
};