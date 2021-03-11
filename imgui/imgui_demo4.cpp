#include "display.h"
#include "glog/logging.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

void GlogSetting(const char* program_name) {
  google::InitGoogleLogging(program_name);
  // capture core dumped
  google::InstallFailureSignalHandler();
  // not write to file
  FLAGS_logtostderr = true;
  google::SetLogDestination(google::INFO, program_name);
}

int main() {
  GlogSetting("test");
  display::DisplayGlfw(720, 480).Update();
}