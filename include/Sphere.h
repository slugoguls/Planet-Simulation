#pragma once

#include <vector>
#include <glm/glm.hpp>

class Sphere {
public:
    Sphere(float radius, int sectorCount, int stackCount);
    ~Sphere();

    void draw() const;

    glm::vec3 getPosition() const;
    void setPosition(const glm::vec3& pos);

    glm::vec3 getVelocity() const;
    void setVelocity(const glm::vec3& vel);

    float getMass() const;
    void setMass(float m);

    void update(float deltaTime);              
    void applyForce(const glm::vec3& force);   

    void setStatic(bool value) { isStatic = value; }
    bool getStatic() const { return isStatic; }

private:
    float radius;
    int sectorCount;
    int stackCount;

    float mass = 1.0f;
    glm::vec3 position{ 0.0f };
    glm::vec3 velocity{ 0.0f };

    unsigned int VAO, VBO, EBO;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    bool isStatic = false;

    void setupSphere();
    void generateVertices();
    void generateIndices();
    void bindBuffers();
    void unbindBuffers();
};
