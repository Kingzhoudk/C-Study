#include "websocketpp/client.hpp"
#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"
#include <map>
#include <memory>
#include <set>
#include <thread>
#include <vector>

class WebsocketServer {
  typedef websocketpp::server<websocketpp::config::asio> Server;

 private:
  uint16_t                  port_;
  Server                    server_;
  std::thread               websocket_server_thread_;

 public:
  WebsocketServer(const uint16_t port);
  void StartRunning();
  void StopRunning();
  void Send(const websocketpp::connection_hdl& hl, const std::string& msg);
};

class WebsocketClient {
  typedef websocketpp::client<websocketpp::config::asio> Client;

 private:
  std::string                 url_;
  Client                      client_;
  std::thread                 websocket_client_thread_;
  websocketpp::connection_hdl server_hdl_;

    public : WebsocketClient(const std::string url);
  void StartRunning();
  void StopRunning();
  void Send(const std::string& msg);
};