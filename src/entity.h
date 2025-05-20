#ifndef ENTITY_H
#define ENTITY_H

#include "model.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Entity {
public:
    Entity(const std::string& path, glm::vec3 pos, glm::vec3 rot = glm::vec3(0), float scale = 1.0f)
        : position(pos), rotation(rot), scale(glm::vec3(scale)), model(nullptr)
    {
        try {
            std::cout << "Loading entity model: " << path << std::endl;
            model = new Model(path.c_str());
            std::cout << "Model loaded: " << (model->isLoaded() ? "SUCCESS" : "FAILED") << std::endl;
            if (!model->isLoaded()) {
                std::cerr << "Failed to load model: " << path << std::endl;
                delete model;
                model = nullptr;
            }
        } catch (const std::exception& e) {
            std::cerr << "Exception loading model: " << e.what() << std::endl;
            if (model) {
                delete model;
                model = nullptr;
            }
        }
    }
    
    // Overload for non-uniform scaling
    Entity(const std::string& path, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
        : position(pos), rotation(rot), scale(scale), model(nullptr)
    {
        try {
            std::cout << "Loading entity model: " << path << std::endl;
            model = new Model(path.c_str());
            if (!model->isLoaded()) {
                std::cerr << "Failed to load model: " << path << std::endl;
                delete model;
                model = nullptr;
            }
        } catch (const std::exception& e) {
            std::cerr << "Exception loading model: " << e.what() << std::endl;
            if (model) {
                delete model;
                model = nullptr;
            }
        }
    }
    
    ~Entity() { delete model; }

    void Draw(Shader& shader) const {
        if (!model) {
            std::cerr << "Cannot draw entity - model not loaded" << std::endl;
            return;
        }
        
        std::cout << "Drawing entity with scale: " << scale.x << ", " << scale.y << ", " << scale.z << std::endl;
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, position);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0,1,0));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1,0,0));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0,0,1));
        modelMatrix = glm::scale(modelMatrix, scale);
        shader.setMat4("model", modelMatrix);
        model->Draw(shader);
    }

    glm::vec3 position, rotation;
    glm::vec3 scale;
private:
    Model* model;
};

#endif 