#pragma once

#include "Entities/DragableParticle.hpp"

class Joint: public DragableParticle
{
    public:
        Joint();
        Joint(float mass, float radius);
};