#include "platform.h"

#include <stdexcept>

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

namespace glab::platform {

static bool initialized = false;

static void OnError(int code, const char* description) { spdlog::error("GLFW ({}): {}", code, description); }

void Init() {
    glfwSetErrorCallback(OnError);
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    initialized = true;
}

void Shutdown() {
    if (initialized) {
        initialized = false;
        glfwTerminate();
    }
}

}  // namespace glab::platform
