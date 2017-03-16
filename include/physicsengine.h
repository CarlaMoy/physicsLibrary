#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include "physicsobject.h"
#include <glm/glm.hpp>
#include <vector>

class PhysicsEngine
{
public:
    PhysicsEngine(){}

    void addObject(const PhysicsObject& object);
    void simulate(float delta);

    void handleCollisions();

    const PhysicsObject& getObject(unsigned int index) const
    {
        return m_objects[index];
    }

    unsigned int getNumObjects() const
    {
        return (unsigned int) m_objects.size();
    }

private:
    std::vector<PhysicsObject> m_objects;
};

#endif // PHYSICSENGINE_H
