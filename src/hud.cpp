#include "hud.h"
#include <sstream>
#include <iomanip>

HUD::HUD() {}

HUD::~HUD() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void HUD::init(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    
    // Configure ImGui style
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 5.0f;
    style.FrameRounding = 3.0f;
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.9f);
}

void HUD::render(const Drone& drone) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    renderTelemetryWindow(drone);
    renderControlsWindow();
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void HUD::renderTelemetryWindow(const Drone& drone) {
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(200, 340), ImGuiCond_FirstUseEver);
    
    ImGui::Begin("Drone Telemetry");
    
    // Position
    glm::vec3 pos = drone.getPosition();
    ImGui::Text("Position:");
    ImGui::Text("X: %.2f", pos.x);
    ImGui::Text("Y: %.2f", pos.y);
    ImGui::Text("Z: %.2f", pos.z);
    ImGui::Separator();
    
    // Rotation
    glm::vec3 rot = drone.getRotation();
    ImGui::Text("Rotation:");
    ImGui::Text("Yaw: %.2f°", rot.y);
    ImGui::Text("Pitch: %.2f°", rot.x);
    ImGui::Text("Roll: %.2f°", rot.z);
    ImGui::Separator();
    
    // Speed and Altitude
    ImGui::Text("Speed: %.2f m/s", drone.getSpeed());
    ImGui::Text("Altitude: %.2f m", drone.getAltitude());
    ImGui::Separator();
    
    // Battery
    float battery = drone.getBatteryLevel();
    ImGui::Text("Battery: %.1f%%", battery);
    ImGui::ProgressBar(battery / 100.0f, ImVec2(-1, 0), "");
    ImGui::Separator();
    
    // GPS
    glm::vec2 gps = drone.getGPSCoordinates();
    ImGui::Text("GPS Coordinates:");
    ImGui::Text("Lat: %.6f", gps.x);
    ImGui::Text("Lon: %.6f", gps.y);
    
    ImGui::End();
}

void HUD::renderControlsWindow() {
    ImGui::SetNextWindowPos(ImVec2(10, 360), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(200, 150), ImGuiCond_FirstUseEver);
    
    ImGui::Begin("Controls");
    ImGui::Text("Movement:");
    ImGui::BulletText("Arrow Keys: Forward/Back/Turn");
    ImGui::BulletText("Space: Ascend");
    ImGui::BulletText("Left Shift: Descend");
    ImGui::Separator();
    ImGui::Text("Camera:");
    ImGui::BulletText("WASD: Move Camera");
    ImGui::BulletText("Mouse: Look Around");
    ImGui::End();
} 