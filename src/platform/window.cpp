#include "config/config.h"
#include "event_manager.h"
#include "events.h"
#include "window.h"

#include <stdexcept>

#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <imgui_impl_glfw.h>

namespace glab::platform {

Window::Window(const char* title, int width, int height) {
    glfwDefaultWindowHints();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config::kGLVersionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config::kGLVersionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (m_native = glfwCreateWindow(width, height, title, nullptr, nullptr); !m_native) {
        throw std::runtime_error("Failed to create window");
    }
    glfwMakeContextCurrent(m_native);
    glfwSwapInterval(1);
    gladLoaderLoadGL();

    glfwSetWindowUserPointer(m_native, this);
    glfwSetFramebufferSizeCallback(m_native, OnFramebufferResize);
    glfwSetKeyCallback(m_native, OnKeyPressed);
    glfwSetMouseButtonCallback(m_native, OnMousePressed);
    glfwSetCursorPosCallback(m_native, OnMouseMove);
    glfwSetScrollCallback(m_native, OnMouseWheel);
}

Window::~Window() { glfwDestroyWindow(m_native); }

void Window::Close() { glfwSetWindowShouldClose(m_native, GLFW_TRUE); }

bool Window::ShouldClose() const { return glfwWindowShouldClose(m_native); }

void Window::PollEvents() { glfwPollEvents(); }

void Window::SwapBuffers() { glfwSwapBuffers(m_native); }

void Window::OnFramebufferResize(GLFWwindow* native, int width, int height) {
    event_manager.Dispatch(FramebufferResizeEvent{width, height});
}

void Window::OnKeyPressed(GLFWwindow* native, int key, int code, int action, int mods) {
    event_manager.Dispatch(KeyPressedEvent{key, code, action, mods});
}

void Window::OnMousePressed(GLFWwindow* native, int button, int action, int mods) {
    event_manager.Dispatch(MousePressedEvent{button, action, mods});
}

void Window::OnMouseMove(GLFWwindow* native, double dx, double dy) { event_manager.Dispatch(MouseMoveEvent{dx, dy}); }

void Window::OnMouseWheel(GLFWwindow* native, double dx, double dy) { event_manager.Dispatch(MouseWheelEvent{dx, dy}); }

GLFWwindow* GetNativeWindow(Window* window) { return window->m_native; }

float GetContentScale(Window* window) { return ImGui_ImplGlfw_GetContentScaleForWindow(window->m_native); }

}  // namespace glab::platform
