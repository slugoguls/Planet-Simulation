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
    this->vertices.clear();
    double x, y, z, xy;
    double sectorStep = 2 * glm::pi<double>() / static_cast<double>(this->sectorCount);
    double stackStep = glm::pi<double>() / static_cast<double>(this->stackCount);
    double sectorAngle, stackAngle;

    for (int i = 0; i <= this->stackCount; ++i) {
        stackAngle = glm::pi<double>() / 2 - i * stackStep;  // from pi/2 to -pi/2
        xy = this->radius * cos(stackAngle);  // r * cos(u)
        z = this->radius * sin(stackAngle);  // r * sin(u)

        for (int j = 0; j <= this->sectorCount; ++j) {
            sectorAngle = j * sectorStep;  // from 0 to 2pi

            x = xy * cos(sectorAngle);   // r * cos(u) * cos(v)
            y = xy * sin(sectorAngle);   // r * cos(u) * sin(v)

            this->vertices.push_back(static_cast<float>(x));
            this->vertices.push_back(static_cast<float>(y));
            this->vertices.push_back(static_cast<float>(z));
        }
    }
}

void Sphere::generateIndices() {
    this->indices.clear();
    int k1, k2;

    for (int i = 0; i < this->stackCount; ++i) {
        k1 = i * (this->sectorCount + 1);     // beginning of current stack
        k2 = k1 + this->sectorCount + 1;      // beginning of next stack

        for (int j = 0; j < this->sectorCount; ++j, ++k1, ++k2) {
            if (i != 0) {
                this->indices.push_back(k1);
                this->indices.push_back(k2);
                this->indices.push_back(k1 + 1);
            }

            if (i != (this->stackCount - 1)) {
                this->indices.push_back(k1 + 1);
                this->indices.push_back(k2);
                this->indices.push_back(k2 + 1);
            }
        }
    }
}

void Sphere::bindBuffers() {
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(float), this->vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), this->indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Sphere::unbindBuffers() {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Sphere::update(double deltaTime) {
    if (this->isStatic) return;

    // Velocity Verlet Integration
    // 1. Calculate new position
    this->position += this->velocity * deltaTime + 0.5 * this->acceleration * deltaTime * deltaTime;

    // 2. Store current acceleration for next step
    glm::dvec3 prevAcceleration = this->acceleration;

    // 3. Calculate new acceleration based on accumulated force
    this->acceleration = this->currentForce / this->mass;

    // 4. Calculate new velocity (using average acceleration)
    this->velocity += 0.5 * (prevAcceleration + this->acceleration) * deltaTime;
}

void Sphere::applyForce(const glm::dvec3& force) {
    this->currentForce += force;
}

void Sphere::resetForce() {
    this->currentForce = glm::dvec3(0.0);
}

glm::dvec3 Sphere::getPosition() const {
    return this->position;
}

void Sphere::setPosition(const glm::dvec3& pos) {
    this->position = pos;
}

glm::dvec3 Sphere::getVelocity() const {
    return this->velocity;
}

void Sphere::setVelocity(const glm::dvec3& vel) {
    this->velocity = vel;
}

float Sphere::getMass() const {
    return this->mass;
}

void Sphere::setMass(double m) {
    this->mass = m;
}