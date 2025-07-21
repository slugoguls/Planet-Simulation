// Planet.h

#pragma once
#include "Sphere.h"
#include <string>

class Planet : public Sphere {
public:
    Planet(float radius, float mass, const glm::dvec3& position, const glm::dvec3& velocity, const std::string& name);

    void update(float deltaTime);
    std::string getName() const;
    void setStatic(bool value) { Sphere::setStatic(value); }
    bool getStatic() const { return Sphere::getStatic(); }

    glm::dvec3 getColor() const { return color; }
    void setColor(const glm::dvec3& c) { color = c; }

private:
    std::string name;
    glm::dvec3 color; // New: Planet color
};
