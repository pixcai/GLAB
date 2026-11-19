#pragma once

#include <GLFW/glfw3.h>

namespace glab::platform {

class Window {
public:
    Window(const char* title, int width, int height);
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

    GLFWwindow* m_native;
};

GLFWwindow* GetNativeWindow(Window* window);
float GetContentScale(Window* window);

}  // namespace glab::platform
