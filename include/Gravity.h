#pragma once

#include <vector>
#include "Sphere.h"

class Gravity {
public:
    Gravity(double G);

    void addObject(Sphere* obj);
    void applyAll(double deltaTime);

private:
    float G;
    std::vector<Sphere*> objects;
};
