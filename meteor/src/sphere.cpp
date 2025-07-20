// Sphere.cpp

#include "Sphere.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <cmath>                   


Sphere::Sphere(float radius, int sectorCount, int stackCount)
    : radius(radius), sectorCount(sectorCount), stackCount(stackCount)
{
    generateVertices();
    generateIndices();
    bindBuffers();
}

Sphere::~Sphere() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Sphere::draw() const {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Sphere::setupSphere() {
    generateVertices();
    generateIndices();
    bindBuffers();
}

void Sphere::generateVertices() {
    vertices.clear();
    float x, y, z, xy;
    float sectorStep = 2 * glm::pi<float>() / static_cast<float>(sectorCount);
    float stackStep = glm::pi<float>() / static_cast<float>(stackCount);
    float sectorAngle, stackAngle;

    for (int i = 0; i <= stackCount; ++i) {
        stackAngle = glm::pi<float>() / 2 - i * stackStep;  // from pi/2 to -pi/2
        xy = radius * cosf(stackAngle);  // r * cos(u)
        z = radius * sinf(stackAngle);  // r * sin(u)

        for (int j = 0; j <= sectorCount; ++j) {
            sectorAngle = j * sectorStep;  // from 0 to 2pi

            x = xy * cosf(sectorAngle);   // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);   // r * cos(u) * sin(v)

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }
    }
}

void Sphere::generateIndices() {
    indices.clear();
    int k1, k2;

    for (int i = 0; i < stackCount; ++i) {
        k1 = i * (sectorCount + 1);     // beginning of current stack
        k2 = k1 + sectorCount + 1;      // beginning of next stack

        for (int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (stackCount - 1)) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
}

void Sphere::bindBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Sphere::unbindBuffers() {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Sphere::update(float deltaTime) {
    position += velocity * deltaTime;
}

void Sphere::applyForce(const glm::vec3& force) {
    glm::vec3 acceleration = force / mass;
    velocity += acceleration;
}

glm::vec3 Sphere::getPosition() const {
    return position;
}

void Sphere::setPosition(const glm::vec3& pos) {
    position = pos;
}

glm::vec3 Sphere::getVelocity() const {
    return velocity;
}

void Sphere::setVelocity(const glm::vec3& vel) {
    velocity = vel;
}

float Sphere::getMass() const {
    return mass;
}

void Sphere::setMass(float m) {
    mass = m;
}