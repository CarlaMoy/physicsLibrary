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

    ~PhysicsEngine();


  //  void initWorld();
    void addObject(const RigidBody& object);
    void simulate(float delta);
    void handleCollisions();
    void updatePhysics(float _time);
    void drawPhysics(const ngl::Mat4 &_globalTx, ngl::Camera *_cam, const std::string _shaderName);
    void setGravity();




    const RigidBody& getObject(unsigned int index) const
    {
        if(index <= m_rigidObjects.size())
            return m_rigidObjects[index];
    }

    unsigned int getNumObjects() const
    {
        return (unsigned int) m_rigidObjects.size();
    }

    static PhysicsEngine* instance();

private:

    std::vector<RigidBody> m_rigidObjects;
    //std::unique_ptr<ngl::AbstractVAO> m_vao;
    bool m_gravOn;
    float m_groundPlane_y = 0.01;
    //ngl::Vec3 m_groundPlane_y = ngl::Vec3(0.0,0.0,0.0);


    void resetRigidBody(RigidBody &io_r);
    void loadRigidBodyVAO();

    static PhysicsEngine *s_instance;

    PhysicsEngine(){}
};

#endif // PHYSICSENGINE_H
