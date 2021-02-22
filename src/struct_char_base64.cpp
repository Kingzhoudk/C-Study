#include <ctime>
#include <iostream>
#include <string.h>
#include <thread>

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

int main(int argc, char** argv) {
  rsu_info_t rsu_info;
  rsu_info.rsu_id = 0;
  rsu_info.posd_3d.x = 1;
  rsu_info.posd_3d.y = 2;
  rsu_info.posd_3d.z = 3;
  rsu_info.is_rsu_valid = true;
  rsu_info.is_rsu_valid = true;
  memset(rsu_info.reserved, 0, sizeof(rsu_info.reserved));
  return 0;
}