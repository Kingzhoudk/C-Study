#include "rpc/server.h"
#include "rpclib_data.h"
#include <ctime>
#include <iostream>
#include <thread>

MsgStruct One(double msg){
  return {
    .test1 = msg,
    .test2 = 2.0,
    .test3 = "server"
  };
}

std::string Two() {
  std::cout << "Two() success\n";
  return "success";
}

int main() {
  rpc::server server(12452);
  // 服务端可以使用一个自定义值（数字、字母等）作为请求参数，该参数绑定一个函数
  server.bind("1", &One);
  server.bind("2", &Two);
  // async_run(worker_threads)，开多个线程保证并发访问
  server.async_run(2);
  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
  }
  return 0;
}