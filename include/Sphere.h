#pragma once

#include <vector>
#include <glm/glm.hpp>

class Sphere {
public:
    Sphere(float radius, int sectorCount, int stackCount);
    ~Sphere();

    void draw() const;

    glm::dvec3 getPosition() const;
    void setPosition(const glm::dvec3& pos);

    glm::dvec3 getVelocity() const;
    void setVelocity(const glm::dvec3& vel);

    float getMass() const;
    void setMass(double m);

    void update(double deltaTime);              
    void applyForce(const glm::dvec3& force);   
    void resetForce();

    void setStatic(bool value) { isStatic = value; }
    bool getStatic() const { return isStatic; }

private:
    float radius;
    int sectorCount;
    int stackCount;

    double mass = 1.0;
    glm::dvec3 position{ 0.0f };
    glm::dvec3 velocity{ 0.0f };
    glm::dvec3 currentForce{ 0.0f }; // New: To accumulate forces
    glm::dvec3 acceleration{ 0.0f }; // New: To store current acceleration

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
