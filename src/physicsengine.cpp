#include "physicsengine.h"
#include "boundingSphere.h"
#include <iostream>
#include <ngl/NGLInit.h>
#include <ngl/Random.h>
#include <ngl/VAOFactory.h>
#include <ngl/SimpleVAO.h>
#include <ngl/Util.h>

PhysicsEngine* PhysicsEngine::s_instance = 0;

PhysicsEngine* PhysicsEngine::instance()
{
    if(!s_instance)
        s_instance = new PhysicsEngine;
    return s_instance;
}


PhysicsEngine::~PhysicsEngine(){}


void PhysicsEngine::addObject(const RigidBody& object)
{
  m_rigidObjects.push_back(object);

}

void PhysicsEngine::simulate(float delta)
{
  for(unsigned int i = 0; i < m_rigidObjects.size(); i++)
  {
    m_rigidObjects[i].integrate(delta);

  }
}

void PhysicsEngine::handleCollisions()
{

  for(unsigned int i = 0; i < m_rigidObjects.size(); i++)
  {
    for(unsigned int j = i + 1; j < m_rigidObjects.size(); j++)
    {
      ///@brief Gets whether objects intersect and the direction of intersection between BoundingSphere-BoundingSphere,
      /// BoundingSphere-AABB, AABB-AABB.
      IntersectData intersectData = m_rigidObjects[i].getCollider().intersect(m_rigidObjects[j].getCollider());


      if(intersectData.GetDoesIntersect())
      {
        ngl::Vec3 direction = intersectData.getDirection();
        direction.normalize();
        m_rigidObjects[i].setVelocity(ngl::Vec3(m_rigidObjects[i].getVelocity().reflect(direction)));
        m_rigidObjects[j].setVelocity(ngl::Vec3(m_rigidObjects[j].getVelocity().reflect(direction)));
      }
    }
  }
}




void PhysicsEngine::updatePhysics(float _time)
{
  std::cout<<"updating\n";
  for(auto& i : m_rigidObjects)
  {
    i.integrate(_time);
    handleCollisions();
  }
}

void PhysicsEngine::drawPhysics(const ngl::Mat4 &_globalTx, ngl::Camera *_cam, const std::string _shaderName)
{
  std::cout<<"drawing\n";
  for(auto& i : m_rigidObjects)
  {
    i.drawRigidBody(_globalTx, _cam, _shaderName);
  }
}



void PhysicsEngine::resetRigidBody(RigidBody &io_r)
{

}

void PhysicsEngine::setGravity()
{
  m_gravOn = !m_gravOn;
}
