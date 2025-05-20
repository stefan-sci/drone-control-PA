#include "drone.h"
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <fstream>

void Drone::moveForward(float deltaTime) {
    float yawRad = glm::radians(rotation.y);
    velocity.x += MOVE_SPEED * deltaTime * sin(yawRad);
    velocity.z += MOVE_SPEED * deltaTime * cos(yawRad);
}

void Drone::moveBackward(float deltaTime) {
    float yawRad = glm::radians(rotation.y);
    velocity.x -= MOVE_SPEED * deltaTime * sin(yawRad);
    velocity.z -= MOVE_SPEED * deltaTime * cos(yawRad);
}

void Drone::moveLeft(float deltaTime) {
    float yawRad = glm::radians(rotation.y);
    velocity.x -= MOVE_SPEED * deltaTime * cos(yawRad);
    velocity.z += MOVE_SPEED * deltaTime * sin(yawRad);
}

void Drone::moveRight(float deltaTime) {
    float yawRad = glm::radians(rotation.y);
    velocity.x += MOVE_SPEED * deltaTime * cos(yawRad);
    velocity.z -= MOVE_SPEED * deltaTime * sin(yawRad);
}

void Drone::ascend(float deltaTime) {
    velocity.y += MOVE_SPEED * deltaTime;
}

void Drone::descend(float deltaTime) {
    velocity.y -= MOVE_SPEED * deltaTime;
}

void Drone::yawLeft(float deltaTime) {
    rotation.y -= ROTATION_SPEED * deltaTime;
}

void Drone::yawRight(float deltaTime) {
    rotation.y += ROTATION_SPEED * deltaTime;
}

void Drone::update(float deltaTime) {
    // Update position based on velocity
    position += velocity * deltaTime;
    
    // Apply simple drag to slow down when no input
    velocity *= 0.95f;
    
    // Calculate current speed
    speed = glm::length(velocity);
    
    // Drain battery based on movement
    batteryLevel -= BATTERY_DRAIN_RATE * deltaTime * (1.0f + speed / MAX_SPEED);
    batteryLevel = std::max(0.0f, batteryLevel);
    
    // Update simulated GPS coordinates
    gpsCoordinates.x += velocity.x * deltaTime * 0.0001f;
    gpsCoordinates.y += velocity.z * deltaTime * 0.0001f;
}

void Drone::Draw(Shader &shader) const {
    shader.use();
    
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));
    
    std::cout << "Drawing drone at position: " << position.x << ", " << position.y << ", " << position.z << std::endl;
    std::cout << "With scale: " << scale << std::endl;
    
    shader.setMat4("model", modelMatrix);
    model->Draw(shader);
}

