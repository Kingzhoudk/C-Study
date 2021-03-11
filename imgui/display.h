#include "glog/logging.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <shared_mutex>
#include <stdio.h>

namespace display {

class DisplayGlfw {
 public:
  DisplayGlfw(const int window_width, const int window_height);
  void Update() {
    // Main loop
    while (!glfwWindowShouldClose(window)) {
      glfwPollEvents();
      // Start the Dear ImGui frame
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();
      imgui->update();
    }
  }

 private:
  GLFWwindow* window;
  const char* glsl_version = "#version 330";
  std::unique_ptr<DisplayImgui> imgui;
};

class DisplayImgui {
 public:
  DisplayImgui(GLFWwindow* window, const char* glsl_version);
  ~DisplayImgui();

  bool update();

  bool open_1, open_2;
  int button_count;
};

}  // namespace display
