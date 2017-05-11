#include "physicsengine.h"
#include "boundingSphere.h"
#include <iostream>
#include <ngl/NGLInit.h>
#include <ngl/Random.h>
#include <ngl/VAOFactory.h>
#include <ngl/SimpleVAO.h>
#include <ngl/Util.h>
#include <ngl/NGLStream.h>

PhysicsEngine* PhysicsEngine::s_instance = 0;

PhysicsEngine* PhysicsEngine::instance()
{
  if(!s_instance)
    s_instance = new PhysicsEngine;
  return s_instance;
}


PhysicsEngine::~PhysicsEngine(){}


void PhysicsEngine::addObject(Collider* _collider, const ngl::Vec3& _velocity, ngl::Vec3 _colour, float _mass)
{
  RigidBody rigidObject(_collider, _velocity, _colour, _mass);
  //   new BoundingSphere(ngl::Vec3(5.0,10.0,1.0), 1.0),ngl::Vec3(5.0,10.0,1.0),ngl::Vec3(1.,1.0,1.0),4.f);
  m_rigidObjects.push_back(rigidObject);

}

/*void PhysicsEngine::addObject(const RigidBody& object)
{
//  RigidBody rigidObject(Collider* _collider, const ngl::Vec3& _velocity, ngl::Vec3 _colour, float _mass
 //       new BoundingSphere(ngl::Vec3(5.0,10.0,1.0), 1.0),ngl::Vec3(5.0,10.0,1.0),ngl::Vec3(1.,1.0,1.0),4.f);
  m_rigidObjects.push_back(object);

}*/

ngl::Vec3 PhysicsEngine::applyForces()
{

  return m_gravity + m_wind;
}

void PhysicsEngine::addWind(ngl::Vec3 _amount)
{
  m_wind += _amount;
}

/*void PhysicsEngine::simulate(float delta)
{
  for(unsigned int i = 0; i < m_rigidObjects.size(); i++)
  {
    m_rigidObjects[i].integrate(delta, applyForces());

  }
}*/

void PhysicsEngine::handleCollisions()
{


  for(unsigned int i = 0; i < m_rigidObjects.size(); ++i)
  {
    for(unsigned int j = i+1; j < m_rigidObjects.size(); ++j)
    {
      // if(i==j) continue;
      ///@brief Gets whether objects intersect and the direction of intersection between BoundingSphere-BoundingSphere,
      /// BoundingSphere-AABB, AABB-AABB.
      IntersectData intersectData = m_rigidObjects[i].transformCollider().intersect(m_rigidObjects[j].transformCollider());
      //  IntersectData groundSphereData = m_rigidObjects[i].getCollider().intersect();
      //   std::cout<<intersectData.GetDoesIntersect()<< "Intersect?\n";
      //   std::cout<<m_rigidObjects[i].getCollider().getSize()<<"Size\n";

      ///@brief Collision response based on intersection of two dynamic rigid bodies
      if(intersectData.GetDoesIntersect())
      {
        ngl::Vec3 direction = intersectData.getDirection();
        direction.normalize();
        m_rigidObjects[i].setVelocity(ngl::Vec3(m_rigidObjects[i].getVelocity().reflect(direction)));
        m_rigidObjects[j].setVelocity(ngl::Vec3(m_rigidObjects[j].getVelocity().reflect(direction)));
      }
    }
    //  std::cout<<m_rigidObjects[i].getPosition().m_y<<"position\n";

  }
}

void PhysicsEngine::checkGroundCollision()
{
  ///@brief Collision response based on objects intersecting the ground plane.
  for(auto& i : m_rigidObjects)
  {
    if((i.getPosition().m_y - i.transformCollider().getSize().m_y) < m_groundPlane_y)
    {
      ngl::Vec3 normal = ngl::Vec3(0.0,1.0,0.0);
      i.setVelocity(ngl::Vec3(i.getVelocity().reflect(normal)));//*0.991));
    }
  }
}


void PhysicsEngine::updatePhysics(float _time)
{
  // std::cout<<"updating\n";
  for(auto& i : m_rigidObjects)
  {
    i.integrate(_time, applyForces());
  }
  handleCollisions();
  checkGroundCollision();
}

void PhysicsEngine::drawPhysics(const ngl::Mat4 &_globalTx, ngl::Camera *_cam, const std::string _shaderName, ngl::Vec3 _colour)
{
  // std::cout<<"drawing\n";
  for(auto& i : m_rigidObjects)
  {
    i.drawRigidBody(_globalTx, _cam, _shaderName, _colour);
  }
}



void PhysicsEngine::resetRigidBody(RigidBody &io_r)
{

}

void PhysicsEngine::setGravity()
{
  m_gravOn = !m_gravOn;
}
