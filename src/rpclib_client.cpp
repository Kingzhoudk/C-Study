#include "rpc/client.h"
#include "rpclib_data.h"
#include <iostream>

int main(int argc, char** argv) {
  auto ip = argv[1];
  int  port = atoi(argv[2]);
  // 创建客户端连接,一直等待连接成功
  rpc::client client(ip, port);

  auto two = client.call("2").as<std::string>();
  std::cout << "two: " << two << "\n";

  // 第一种请求方式
  auto msgdata1 = client.call("1", 123).as<MsgStruct>();
  std::cout << "msgdata: test1= " << msgdata1.test1 << " test2:" << msgdata1.test2 << " test3:" << msgdata1.test3
            << "\n";

  // 第二种async请求方式
  auto one = client.async_call("1", 456);
  auto msgdata2 = one.get().as<MsgStruct>();
  std::cout << "msgdata: test1= " << msgdata2.test1 << " test2:" << msgdata2.test2 << " test3:" << msgdata2.test3
            << "\n";

  while (true) {
    // 第一种请求方式
    auto msgdata1 = client.call("1", 123).as<MsgStruct>();
    std::cout << "msgdata: test1= " << msgdata1.test1 << " test2:" << msgdata1.test2 << " test3:" << msgdata1.test3
              << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    // 20ms
  }
  return 0;
}