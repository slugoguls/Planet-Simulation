// Planet.cpp

#include "Planet.h"

Planet::Planet(float radius, float mass, const glm::vec3& position, const glm::vec3& velocity, const std::string& name)
    : Sphere(radius, 36, 18), name(name) {
    setMass(mass);
    setPosition(position);
    setVelocity(velocity);
}

void Planet::update(float deltaTime) {
    Sphere::update(deltaTime);
}

std::string Planet::getName() const {
    return name;
}
