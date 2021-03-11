#include "display.h"

static void glfw_error_callback(int error, const char* description) {
  fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

namespace display {

DisplayGlfw::DisplayGlfw(const int window_width, const int window_height)
  : window(),
    glsl_version("#version 330"),
    imgui(nullptr) {
  // 实例化glfw窗口
  glfwSetErrorCallback(glfw_error_callback);  //设置失败回调函数
  if (!glfwInit())
    LOG(FATAL) << "creat glfw failed.";
  // 配置GLFW
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);           // (GL_TRUE)3.0+ only,(GL_FALSE)enable LineWidth, PointSize

  // 创建窗口对象，这个窗口对象存放了所有和窗口相关的数据，而且会被GLFW的其他函数频繁地用到。
  window = glfwCreateWindow(window_width, window_height, "Test", NULL, NULL);
  if (window == NULL) {
    glfwTerminate();
    LOG(FATAL) << "creat glfw failed.";
  }
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);  // Enable vsync

  // Initialize OpenGL loader
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    LOG(FATAL) << "Failed to initialize OpenGL loader!";
  }

  imgui = std::make_unique<DisplayImgui>(window, glsl_version);
}

DisplayImgui::DisplayImgui(GLFWwindow* window, const char* glsl_version) {
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  //ImGui::StyleColorsClassic();

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);
}

bool DisplayImgui::update() {
  ImGui::Begin("menu");

  ImGui::Text("This is some useful text.");           // Display some text (you can use a format strings too)
  ImGui::Checkbox("Open 1", &open_1);  // Edit bools storing our window open/close state
  ImGui::Checkbox("Open 2", &open_2);

  if (ImGui::Button("Button"))  // Buttons return true when clicked (most widgets return true when edited/activated)
    button_count++;
  ImGui::SameLine();
  ImGui::Text("counter = %d", button_count);

  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  ImGui::End();
}

}  // namespace display