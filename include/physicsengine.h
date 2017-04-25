#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include "rigidBody.h"
#include <glm/glm.hpp>
#include <vector>
#include <ngl/SimpleVAO.h>
#include <memory>

class PhysicsEngine
{
public:
    PhysicsEngine(){}

    void addObject(const RigidBody& object);
    void simulate(float delta);
    void handleCollisions();
    void updatePhysics();
    void drawPhysics();



    const RigidBody& getObject(unsigned int index) const
    {
        return m_rigidObjects[index];
    }

    unsigned int getNumObjects() const
    {
        return (unsigned int) m_rigidObjects.size();
    }

private:
    std::vector<RigidBody> m_rigidObjects;
    std::unique_ptr<ngl::AbstractVAO> m_vao;

    void resetRigidBody(RigidBody &io_r);
    void loadRigidBodyVAO();
};

#endif // PHYSICSENGINE_H
