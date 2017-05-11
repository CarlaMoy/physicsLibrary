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
   // void addObject(const RigidBody& object);
    void addObject(Collider* _collider, const ngl::Vec3& _velocity, ngl::Vec3 _colour, float _mass);
  //  void simulate(float delta);
    void handleCollisions();
    void checkGroundCollision();
    void updatePhysics(float _time);
    void drawPhysics(const ngl::Mat4 &_globalTx, ngl::Camera *_cam, const std::string _shaderName, ngl::Vec3 _colour);
    void setGravity();
    ngl::Vec3 applyForces();
    void addWind(ngl::Vec3 _amount);




    RigidBody getObject(unsigned int index) const
    {
        if(index <= m_rigidObjects.size())
            return m_rigidObjects[index];
        else
          std::cerr << "Error: getObject(index) is out of range.\n";
          exit(1);
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
    ngl::Vec3 m_gravity = ngl::Vec3(0.0,-9.8,0.0);
    ngl::Vec3 m_wind;

    //ngl::Vec3 m_groundPlane_y = ngl::Vec3(0.0,0.0,0.0);


    void resetRigidBody(RigidBody &io_r);
    void loadRigidBodyVAO();

    static PhysicsEngine *s_instance;

    PhysicsEngine(){}
};

#endif // PHYSICSENGINE_H
