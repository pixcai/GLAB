#pragma once

struct GLFWwindow;

class GUI final {
public:
    GUI(GLFWwindow* window);

    void render();

private:
    void renderMainMenuBar();
    void renderStatusBar();
    void initLayout();
    void renderWorkspace();
    void renderInspector();
};
