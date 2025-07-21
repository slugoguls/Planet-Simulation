// Planet.cpp

#include "Planet.h"

Planet::Planet(float radius, float mass, const glm::dvec3& position, const glm::dvec3& velocity, const std::string& name)
    : Sphere(radius, 36, 18), name(name), color(1.0, 1.0, 1.0) { // Default to white
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
