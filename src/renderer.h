#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "shader.h"
#include "drone.h"
#include "entity.h"
#include <iostream>

class Renderer {
public:
    void init() {
        shader.use();
    }
    
    void render(const Drone& drone, const glm::mat4& view, const glm::mat4& projection) {
        shader.use();
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        drone.Draw(shader);
    }

    void render(const Entity& entity, const glm::mat4& view, const glm::mat4& projection) {
        shader.use();
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        entity.Draw(shader);
    }

private:
    Shader shader{"shaders/drone.vert", "shaders/drone.frag"};
}; 