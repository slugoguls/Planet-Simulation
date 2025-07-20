#pragma once

#include <vector>
#include "Sphere.h"

class Gravity {
public:
    Gravity(float G);

    void addObject(Sphere* obj);
    void applyAll(float deltaTime);

private:
    float G;
    std::vector<Sphere*> objects;
};
