#include "../config.h"
#include "window.h"

#include <cstdlib>

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#define USER_POINTER() static_cast<Window*>(glfwGetWindowUserPointer(handle))

namespace glab {

void Window::OnFramebufferResizeCallback(GLFWwindow* handle, int width, int height) {
    FramebufferResizeEvent event{width, height};

    for (auto callback : USER_POINTER()->m_framebuffer_resize_event_callbacks) {
        callback(event);
    }
}

void Window::OnKeyCallback(GLFWwindow* handle, int key, int scancode, int action, int mods) {
    KeyEvent event{key, scancode, action, mods};

    for (auto callback : USER_POINTER()->m_key_event_callbacks) {
        callback(event);
    }
}

void Window::OnMouseButtonCallback(GLFWwindow* handle, int button, int action, int mods) {
    MouseButtonEvent event{button, action, mods};

    for (auto callback : USER_POINTER()->m_mouse_button_event_callbacks) {
        callback(event);
    }
}

Window::Window(std::string_view title, int width, int height) {
    glfwDefaultWindowHints();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config::kGLVersionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config::kGLVersionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_handle = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
    if (!m_handle) {
        spdlog::critical("Failed to create window: {}", title);
        std::exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(m_handle);
    glfwSwapInterval(1);

    glfwSetWindowUserPointer(m_handle, this);
    glfwSetFramebufferSizeCallback(m_handle, OnFramebufferResizeCallback);
    glfwSetKeyCallback(m_handle, OnKeyCallback);
    glfwSetMouseButtonCallback(m_handle, OnMouseButtonCallback);

    glfwGetFramebufferSize(m_handle, &m_framebuffer_size.x, &m_framebuffer_size.y);
}

Window::~Window() { Close(); }

void Window::Close() {
    if (m_handle) {
        glfwDestroyWindow(m_handle);
        m_handle = nullptr;
    }
}

bool Window::ShouldClose() const { return glfwWindowShouldClose(m_handle); }

bool Window::IsMinimized() const { return glfwGetWindowAttrib(m_handle, GLFW_ICONIFIED) != 0; }

}  // namespace glab
