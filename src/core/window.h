#pragma once

#include <functional>
#include <string_view>
#include <vector>

#define GLFW_INCLUDE_NONE 1
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace glab {

struct FramebufferResizeEvent {
    int width;
    int height;
};

struct KeyEvent {
    int key;
    int scancode;
    int action;
    int mods;
};

struct MouseButtonEvent {
    int button;
    int action;
    int mods;
};

class Window {
public:
    static void OnFramebufferResizeCallback(GLFWwindow* handle, int width, int height);
    static void OnKeyCallback(GLFWwindow* handle, int key, int scancode, int action, int mods);
    static void OnMouseButtonCallback(GLFWwindow* handle, int button, int action, int mods);

public:
    Window(std::string_view title, int width, int height);
    ~Window();

    void Close();
    bool ShouldClose() const;
    bool IsMinimized() const;
    glm::ivec2 GetFramebufferSize() const { return m_framebuffer_size; }

    template <typename EventT>
    void AddListener(std::function<void(const EventT& event)> callback) {
        if constexpr (std::is_same_v<EventT, FramebufferResizeEvent>) {
            m_framebuffer_resize_event_callbacks.emplace_back(std::move(callback));
        } else if constexpr (std::is_same_v<EventT, KeyEvent>) {
            m_key_event_callbacks.emplace_back(std::move(callback));
        } else if constexpr (std::is_same_v<EventT, MouseButtonEvent>) {
            m_mouse_button_event_callbacks.emplace_back(std::move(callback));
        } else {
            static_assert(std::is_same_v<EventT, void>, "Unsupported event type");
        }
    }

    template <typename EventT>
    void RemoveListener(std::function<void(const EventT& event)> callback) {}

private:
    GLFWwindow* m_handle;
    glm::ivec2 m_framebuffer_size;
    std::vector<std::function<void(const FramebufferResizeEvent& event)>> m_framebuffer_resize_event_callbacks;
    std::vector<std::function<void(const KeyEvent& event)>> m_key_event_callbacks;
    std::vector<std::function<void(const MouseButtonEvent& event)>> m_mouse_button_event_callbacks;
};

}  // namespace glab
