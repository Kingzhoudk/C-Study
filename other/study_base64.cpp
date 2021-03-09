#include "json/json.hpp"
#include <ctime>
#include <iostream>
#include <string.h>
#include <thread>
#include <websocketpp/base64/base64.hpp>

struct pose_3d_t {
  double x = 0.0;
  double y = 0.0;
  double z = 0.0;
};

struct rsu_info_t {
  int32_t rsu_id;    /* rsu ID */
  pose_3d_t posd_3d; /* 3d pose */
  bool is_rsu_valid; /* is rsu valid */
  char reserved[16];
};

unsigned int Base64_encodeLength(const unsigned char* in, unsigned int in_len) {
  return ((4u * in_len / 3u) + 3u) & ~0x3;
}
unsigned int Base64_encode(char* out, unsigned int out_len, const unsigned char* in, unsigned int in_len) {
  static const char BASE64_ENCODE_TABLE[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/=";
  unsigned int ret = 0u;
  unsigned int out_count = 0u;
  while (in_len > 0u && out_count < out_len) {
    int i;
    unsigned char c[] = { 0, 0, 64, 64 }; /* index of '=' char */
    /* first character */
    i = *in;
    c[0] = (i & ~0x3) >> 2;
    /* second character */
    c[1] = (i & 0x3) << 4;
    --in_len;
    if (in_len > 0u) {
      ++in;
      i = *in;
      c[1] |= (i & ~0xF) >> 4;
      /* third character */
      c[2] = (i & 0xF) << 2;
      --in_len;
      if (in_len > 0u) {
        ++in;
        i = *in;
        c[2] |= (i & ~0x3F) >> 6;
        /* fourth character */
        c[3] = (i & 0x3F);
        --in_len;
        ++in;
      }
    }
    /* encode the characters */
    out_count += 4u;
    for (i = 0; i < 4 && out_count <= out_len; ++i, ++out)
      *out = BASE64_ENCODE_TABLE[c[i]];
  }
  if (out_count <= out_len) {
    if (out_count < out_len)
      *out = '\0';
    ret = out_count;
  }
  return ret;
}

std::string PackRsuInfoBase64(const rsu_info_t& rsu_info) {
  constexpr auto data_len = sizeof(rsu_info_t);
  unsigned char data_base64[data_len];
  memcpy(data_base64, &rsu_info, data_len);
  return websocketpp::base64_encode(data_base64, data_len);
}

int main(int argc, char** argv) {
  rsu_info_t rsu_info;
  rsu_info.rsu_id = 0;
  rsu_info.posd_3d.x = 1;
  rsu_info.posd_3d.y = 2;
  rsu_info.posd_3d.z = 3;
  rsu_info.is_rsu_valid = true;
  rsu_info.is_rsu_valid = true;
  // std::cout << rsu_info << "\n";
  memset(rsu_info.reserved, 0, sizeof(rsu_info.reserved));
  std::cout << PackRsuInfoBase64(rsu_info) << "\n";

  char rsuinfo_base64[120];

  constexpr auto data_len = sizeof(rsu_info_t);
  uint8_t data[data_len];
  memcpy(data, &rsu_info, data_len);

  memset(rsuinfo_base64, 'A', 120);
  Base64_encode(rsuinfo_base64, Base64_encodeLength(nullptr, data_len), data, data_len);

  std::cout << rsuinfo_base64 << "\n";

  nlohmann::json msg = nlohmann::json{ "T1", { "1", "2" }, { "1", "3" } };
  std::cout << msg.dump() << "\n";
  return 0;
}