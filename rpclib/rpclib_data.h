#include "rpc/msgpack.hpp"
#include <iostream>
#include <vector>

// 自定义数据结构
struct MsgStruct {
  double      test1;
  float       test2;
  std::string test3;

  // 打包序列
  MSGPACK_DEFINE_ARRAY(test1, test2, test3)
};