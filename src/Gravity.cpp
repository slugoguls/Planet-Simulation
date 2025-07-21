#include "Gravity.h"

Gravity::Gravity(double G) : G(G) {}

void Gravity::addObject(Sphere* obj) {
    objects.push_back(obj);
}

void Gravity::applyAll(double deltaTime) {
    // Reset forces for all objects
    for (Sphere* obj : objects) {
        obj->resetForce();
    }

    // Apply gravitational forces
    for (size_t i = 0; i < objects.size(); ++i) {
        for (size_t j = i + 1; j < objects.size(); ++j) {
            Sphere* a = objects[i];
            Sphere* b = objects[j];

            glm::dvec3 direction = b->getPosition() - a->getPosition();
            double distance = glm::length(direction);

            if (distance < 10.0) continue;

            glm::dvec3 forceDir = glm::normalize(direction);
            double forceMag = G * a->getMass() * b->getMass() / (distance * distance);
            glm::dvec3 force = forceDir * forceMag;

            if (!a->getStatic()) a->applyForce(force);
            if (!b->getStatic()) b->applyForce(-force);
        }
    }

    // Update positions and velocities using accumulated forces
    for (Sphere* obj : objects) {
        obj->update(deltaTime);
    }
}