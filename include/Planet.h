// Planet.h

#pragma once
#include "Sphere.h"
#include <string>

class Planet : public Sphere {
public:
    Planet(float radius, float mass, const glm::vec3& position, const glm::vec3& velocity, const std::string& name);

    void update(float deltaTime);
    std::string getName() const;
    void setStatic(bool value) { Sphere::setStatic(value); }
    bool getStatic() const { return Sphere::getStatic(); }

private:
    std::string name;
};
