#include "config/config.h"
#include "core/event/event_emitter.h"
#include "window.h"

#include <stdexcept>

#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <imgui_impl_glfw.h>

#define USER_POINTER() static_cast<Window*>(glfwGetWindowUserPointer(native))

namespace glab::platform {

Window::Window(const char* title, int width, int height, event::EventEmitter& event_emitter)
    : m_event_emitter(event_emitter) {
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
    USER_POINTER()->m_event_emitter.Emit(event::FramebufferResizeEvent{.width = width, .height = height});
}

void Window::OnKeyPressed(GLFWwindow* native, int key, int code, int action, int mods) {
    USER_POINTER()->m_event_emitter.Emit(
        event::KeyPressedEvent{.key = key, .code = code, .action = action, .mods = mods});
}

void Window::OnMousePressed(GLFWwindow* native, int button, int action, int mods) {
    USER_POINTER()->m_event_emitter.Emit(event::MousePressedEvent{.button = button, .action = action, .mods = mods});
}

void Window::OnMouseMove(GLFWwindow* native, double dx, double dy) {
    USER_POINTER()->m_event_emitter.Emit(event::MouseMoveEvent{.dx = dx, .dy = dy});
}

void Window::OnMouseWheel(GLFWwindow* native, double dx, double dy) {
    USER_POINTER()->m_event_emitter.Emit(event::MouseWheelEvent{.dx = dx, .dy = dy});
}

GLFWwindow* GetNativeWindow(Window* window) { return window->m_native; }

float GetContentScale(Window* window) { return ImGui_ImplGlfw_GetContentScaleForWindow(window->m_native); }

}  // namespace glab::platform
