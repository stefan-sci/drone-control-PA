#pragma once
#include "drone.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class HUD {
public:
    HUD();
    ~HUD();
    
    void init(GLFWwindow* window);
    void render(const Drone& drone);

private:
    void renderTelemetryWindow(const Drone& drone);
    void renderControlsWindow();
}; 