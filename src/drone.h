#ifndef DRONE_H
#define DRONE_H

#include "model.h"
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <fstream>

class Drone {
private:
    Model* model;
    glm::vec3 position;
    glm::vec3 rotation;
    float scale;

public:
    // Constants
    const float MOVE_SPEED = 10.0f;
    const float ROTATION_SPEED = 90.0f;
    const float MAX_SPEED = 10.0f;
    const float BATTERY_DRAIN_RATE = 0.05f;
    
    // Constructor
    Drone() : position(0.0f, 0.0f, 0.0f), rotation(0.0f), scale(10.0f) {
        std::cout << "Drone model path: " << "models/drone/Drone_obj.obj" << std::endl;
        // Check if the texture files exist
        std::ifstream file1("models/drone/Drone_obj.mtl");
        std::cout << "Drone MTL file exists: " << (file1.good() ? "YES" : "NO") << std::endl;
        file1.close();
        
        try {
            model = new Model("models/drone/Drone_obj.obj");
        } catch (const std::exception& e) {
            std::cerr << "Failed to load drone model: " << e.what() << std::endl;
            model = nullptr;
        }
    }
    
    ~Drone() {
        if (model) delete model;
    }
    
    void Draw(Shader &shader) const;

    // Add getters/setters for position, rotation, scale
    void setPosition(const glm::vec3& pos) { position = pos; }
    void setRotation(const glm::vec3& rot) { rotation = rot; }
    void setScale(float s) { scale = s; }

    // Movement commands
    void moveForward(float deltaTime);
    void moveBackward(float deltaTime);
    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);
    void ascend(float deltaTime);
    void descend(float deltaTime);
    void yawLeft(float deltaTime);
    void yawRight(float deltaTime);
    
    // Telemetry data
    glm::vec3 getPosition() const { return position; }
    glm::vec3 getRotation() const { return rotation; }
    float getAltitude() const { return position.y; }
    float getBatteryLevel() const { return batteryLevel; }
    glm::vec2 getGPSCoordinates() const { return gpsCoordinates; }
    float getSpeed() const { return speed; }
    float getScale() const { return scale; }
    
    // Update drone state
    void update(float deltaTime);

private:
    glm::vec3 velocity{0.0f};      // Current velocity
    float speed{0.0f};             // Current speed
    float batteryLevel{100.0f};    // Battery percentage
    glm::vec2 gpsCoordinates{0.0f};// Simulated GPS coordinates
};

#endif 