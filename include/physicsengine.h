#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include "rigidBody.h"
#include <glm/glm.hpp>
#include <vector>
#include <ngl/SimpleVAO.h>
#include <memory>
#include "RigidBodyOctree.h"

///@file aabb.h
///@brief AABB Class, child class of Collider for generating and checking AABB based collision.
///@author Carla Moy
///@class AABB

class PhysicsEngine
{
public:

    ~PhysicsEngine();


  //  void initWorld();
   // void addObject(const RigidBody& object);
    void addObject(const RigidBody& object);//Collider* _collider, const ngl::Vec3& _velocity, ngl::Vec3 _colour, float _mass, float _frictionCoeff);
  //  void simulate(float delta);
    void handleCollisions();
    void checkGroundWallCollision();
    void updatePhysics(float _time);
    void drawPhysics(const ngl::Mat4 &_globalTx, ngl::Camera *_cam, const std::string _shaderName, ngl::Vec3 _colour);
    void setGravity(float _value){m_gravity.m_y = _value;}
    void setRestitutionCoeff(float _restitution) {m_restitutionCoeff = _restitution;}
    ngl::Vec3 applyWorldForces();
    void addWind(ngl::Vec3 _amount);
    void resetForces();
    void resetWorld() {m_rigidObjects.clear();}
    void setBoundingArea(bool _choice) {m_boundingAreaOn = _choice;}




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
    std::vector <RigidBody *> m_rigidObjs;
    //std::unique_ptr<ngl::AbstractVAO> m_vao;
    bool m_boundingAreaOn = true;
    float m_groundPlane_y = 0.0f;
    ngl::Vec3 m_gravity;// = ngl::Vec3(0.0,-9.8,0.0);
    ngl::Vec3 m_wind;
    float m_restitutionCoeff = 0.5;

    //ngl::Vec3 m_groundPlane_y = ngl::Vec3(0.0,0.0,0.0);


    void resetRigidBody(RigidBody &io_r);
  //  void loadRigidBodyVAO();

    static PhysicsEngine *s_instance;

    /// @brief octree for collision detection
   // std::unique_ptr<RigidBodyOctree>  m_collisionTree;

    PhysicsEngine(){}
};

#endif // PHYSICSENGINE_H
