#include "Joint.hpp"
#include "Entities/DragableParticle.hpp"

Joint::Joint()
    : DragableParticle(0, 0)
{
    
}

Joint::Joint(float mass, float radius)
    : DragableParticle(mass, radius)
{

}