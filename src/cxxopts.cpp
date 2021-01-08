#include "cxxopts/cxxopts.hpp"

int main(int argc, char** argv) {
  // 创建一个cxxopts实例
  cxxopts::Options options(argv[0]);
  // 增加选项
  options.add_options()
    ("h,help", "print help and version")
    ("v,version", "print version")
    ("c,config", "print config", cxxopts::value<std::string>()->default_value("config"))
    ("n,number", "print bumber", cxxopts::value<int>()->default_value(std::to_string(1212)))
    ("f,file", "print file", cxxopts::value<std::string>()->implicit_value("file"))
  ;
  // 帮助的第一行中程序名后面的字符串被调用options.custom_help完全替换。
  options.custom_help("[config number]");
  // 不输入参数，直接在后面按照顺序输入
  options.parse_positional({ "config", "number" });
  //解析命令行
  const cxxopts::ParseResult parse_option_result = options.parse(argc, argv);

  if (parse_option_result.count("h")) {
    std::cout << options.help() << "\n";
    return 0;
  }
  if (parse_option_result.count("v")) {
    std::cout << "V1.1.0\n";
    return 0;
  }
  std::cout << "config:" << parse_option_result["c"].as<std::string>() << "\n";
  std::cout << "number:" << parse_option_result["n"].as<int>() << "\n";
  if (parse_option_result.count("f")) {
    std::cout << "file:" << parse_option_result["f"].as<std::string>() << "\n";
  }
  return 0;
}