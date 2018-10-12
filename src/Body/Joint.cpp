#include "Joint.hpp"
#include "Particle.hpp"

Joint::Joint()
    : Particle(0, 0)
{
    
}

Joint::Joint(float mass, float radius)
    : Particle(mass, radius)
{

}