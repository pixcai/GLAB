#pragma once

#include "core/event/event_emitter.h"

#include <GLFW/glfw3.h>

namespace glab::platform {

class Window {
public:
    Window(const char* title, int width, int height, event::EventEmitter& event_emitter);
    ~Window();

    void Close();
    bool ShouldClose() const;

    void PollEvents();
    void SwapBuffers();

private:
    static void OnFramebufferResize(GLFWwindow* native, int width, int height);
    static void OnKeyPressed(GLFWwindow* native, int key, int code, int action, int mods);
    static void OnMousePressed(GLFWwindow* native, int button, int action, int mods);
    static void OnMouseMove(GLFWwindow* native, double dx, double dy);
    static void OnMouseWheel(GLFWwindow* native, double dx, double dy);

private:
    friend GLFWwindow* GetNativeWindow(Window* window);
    friend float GetContentScale(Window* window);

    event::EventEmitter& m_event_emitter;
    GLFWwindow* m_native;
};

GLFWwindow* GetNativeWindow(Window* window);
float GetContentScale(Window* window);

}  // namespace glab::platform
