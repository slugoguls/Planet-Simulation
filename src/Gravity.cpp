#include "Gravity.h"

Gravity::Gravity(float G) : G(G) {}

void Gravity::addObject(Sphere* obj) {
    objects.push_back(obj);
}

void Gravity::applyAll(float deltaTime) {
    for (size_t i = 0; i < objects.size(); ++i) {
        for (size_t j = i + 1; j < objects.size(); ++j) {
            Sphere* a = objects[i];
            Sphere* b = objects[j];

            glm::vec3 direction = b->getPosition() - a->getPosition();
            float distance = glm::length(direction);

            if (distance < 0.1f) continue;

            glm::vec3 forceDir = glm::normalize(direction);
            float forceMag = G * a->getMass() * b->getMass() / (distance * distance);
            glm::vec3 force = forceDir * forceMag;

            if (!a->getStatic()) a->applyForce(force);
            if (!b->getStatic()) b->applyForce(-force);
        }
    }
}