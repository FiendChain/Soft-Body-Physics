#pragma once

#include "Particle.hpp"

class Joint: public Particle
{
    public:
        Joint();
        Joint(float mass, float radius);
};