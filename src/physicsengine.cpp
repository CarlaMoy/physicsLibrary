#include "physicsengine.h"
#include "boundingSphere.h"
#include <iostream>
#include <ngl/NGLInit.h>
#include <ngl/Random.h>
#include <ngl/VAOFactory.h>
#include <ngl/SimpleVAO.h>
#include <ngl/Util.h>
#include <ngl/NGLStream.h>
#include <boost/foreach.hpp>
#include "rigidBody.h"

PhysicsEngine* PhysicsEngine::s_instance = 0;

PhysicsEngine* PhysicsEngine::instance()
{
  if(!s_instance)
    s_instance = new PhysicsEngine;
  return s_instance;
}


PhysicsEngine::~PhysicsEngine()
{
//  BOOST_FOREACH(RigidBody *p, m_rigidObjs)
//  {
//      delete p;
//  }
}


void PhysicsEngine::addObject(const RigidBody& object)//Collider* _collider, const ngl::Vec3& _velocity, ngl::Vec3 _colour, float _mass, float _frictionCoeff)
{
 // RigidBody rigidObject(_collider, _velocity, _colour, _mass, _frictionCoeff);
  //   new BoundingSphere(ngl::Vec3(5.0,10.0,1.0), 1.0),ngl::Vec3(5.0,10.0,1.0),ngl::Vec3(1.,1.0,1.0),4.f);
  m_rigidObjects.push_back(object);


}

/*void PhysicsEngine::addObject(const RigidBody& object)
{
//  RigidBody rigidObject(Collider* _collider, const ngl::Vec3& _velocity, ngl::Vec3 _colour, float _mass
 //       new BoundingSphere(ngl::Vec3(5.0,10.0,1.0), 1.0),ngl::Vec3(5.0,10.0,1.0),ngl::Vec3(1.,1.0,1.0),4.f);
  m_rigidObjects.push_back(object);

}*/



ngl::Vec3 PhysicsEngine::applyWorldForces()
{

  return m_gravity + m_wind;
}

void PhysicsEngine::addWind(ngl::Vec3 _amount)
{
  m_wind += _amount;
}

void PhysicsEngine::resetForces()
{
  for(auto& i : m_rigidObjects)
  {
    i.setVelocity(ngl::Vec3::zero());
    //i.se
  }
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

 /* m_collisionTree->clearTree();

  BOOST_FOREACH(RigidBody *p, m_rigidObjs)
  {
      m_collisionTree->addObject(p);
  }
  m_collisionTree->checkCollision();*/

  for(unsigned int i = 0; i < m_rigidObjects.size(); ++i)
  {
    for(unsigned int j = i+1; j < m_rigidObjects.size(); ++j)
    {
      // if(i==j) continue;
      ///@brief Gets whether objects intersect and the direction of intersection between BoundingSphere-BoundingSphere,
      /// BoundingSphere-AABB, AABB-AABB.
      IntersectData intersectData = m_rigidObjects[i].transformCollider().intersect(m_rigidObjects[j].transformCollider());
     // std::cout<<intersectData.GetDoesIntersect()<<"---------\n";

      ///@brief Collision response based on intersection of two dynamic rigid bodies
      if(intersectData.GetDoesIntersect())
      {
        ngl::Vec3 direction = intersectData.getDirection();
        //direction.normalize();
   //     float mass1 = 1 / m_rigidObjects[i].getMass();
   //     float mass2 = 1 / m_rigidObjects[j].getMass();
   //     float totalMass = mass1 + mass2;
     //   m_rigidObjects[i].setVelocity(ngl::Vec3(m_rigidObjects[i].getVelocity().reflect(direction))/(m_rigidObjects[i].getMass()));
     //   m_rigidObjects[j].setVelocity(ngl::Vec3(m_rigidObjects[j].getVelocity().reflect(direction))/(m_rigidObjects[j].getMass()));//*m_rigidObjects[j].getFrictionCoeff());

        ngl::Vec3 relativeVel = m_rigidObjects[j].getVelocity() - m_rigidObjects[i].getVelocity();

        float velAlongNormal = relativeVel.dot(direction);

        //Do not resolve if velocities are moving away
        if(velAlongNormal > 0)
          continue;

      //  float speed_i = m_rigidObjects[i].getVelocity().length();
      //  float speed_j = m_rigidObjects[j].getVelocity().length();

        //Modified from : https://gamedevelopment.tutsplus.com/tutorials/when-worlds-collide-simulating-circle-circle-collisions--gamedev-769

//        float newVel_ix = m_rigidObjects[i].getVelocity().m_x * (m_rigidObjects[i].getMass() - m_rigidObjects[j].getMass()) +
//                                                        (2 * m_rigidObjects[j].getMass() * m_rigidObjects[j].getVelocity().m_x)
//                                                        / (m_rigidObjects[i].getMass() + m_rigidObjects[j].getMass());
//        float newVel_iy = m_rigidObjects[i].getVelocity().m_y * (m_rigidObjects[i].getMass() - m_rigidObjects[j].getMass()) +
//                                                        (2 * m_rigidObjects[j].getMass() * m_rigidObjects[j].getVelocity().m_y)
//                                                        / (m_rigidObjects[i].getMass() + m_rigidObjects[j].getMass());
//        float newVel_iz = m_rigidObjects[i].getVelocity().m_z * (m_rigidObjects[i].getMass() - m_rigidObjects[j].getMass()) +
//                                                        (2 * m_rigidObjects[j].getMass() * m_rigidObjects[j].getVelocity().m_z)
//                                                        / (m_rigidObjects[i].getMass() + m_rigidObjects[j].getMass());

//        float newVel_jx = m_rigidObjects[j].getVelocity().m_x * (m_rigidObjects[j].getMass() - m_rigidObjects[i].getMass()) +
//                                                        (2 * m_rigidObjects[i].getMass() * m_rigidObjects[i].getVelocity().m_x)
//                                                        / (m_rigidObjects[j].getMass() + m_rigidObjects[i].getMass());
//        float newVel_jy = m_rigidObjects[j].getVelocity().m_y * (m_rigidObjects[j].getMass() - m_rigidObjects[i].getMass()) +
//                                                        (2 * m_rigidObjects[i].getMass() * m_rigidObjects[i].getVelocity().m_y)
//                                                        / (m_rigidObjects[j].getMass() + m_rigidObjects[i].getMass());
//        float newVel_jz = m_rigidObjects[j].getVelocity().m_z * (m_rigidObjects[j].getMass() - m_rigidObjects[i].getMass()) +
//                                                        (2 * m_rigidObjects[i].getMass() * m_rigidObjects[i].getVelocity().m_z)
//                                                        / (m_rigidObjects[j].getMass() + m_rigidObjects[i].getMass());


        //Formula for elactic/ inelastic collision from : https://en.wikipedia.org/wiki/Inelastic_collision

        ngl::Vec3 newVel_i = (m_rigidObjects[j].getMass() * m_restitutionCoeff *
                          (m_rigidObjects[j].getVelocity() - m_rigidObjects[i].getVelocity()) +
                          m_rigidObjects[i].getMass() * m_rigidObjects[i].getVelocity() +
                          m_rigidObjects[j].getMass() * m_rigidObjects[j].getVelocity()) /
                          (m_rigidObjects[i].getMass() + m_rigidObjects[j].getMass());

        ngl::Vec3 newVel_j = (m_rigidObjects[i].getMass() * m_restitutionCoeff *
                          (m_rigidObjects[i].getVelocity() - m_rigidObjects[j].getVelocity()) +
                          m_rigidObjects[j].getMass() * m_rigidObjects[j].getVelocity() +
                          m_rigidObjects[i].getMass() * m_rigidObjects[i].getVelocity()) /
                          (m_rigidObjects[j].getMass() + m_rigidObjects[i].getMass());


//        //calculate restitution
//        float e = (m_rigidObjects[i].getRestitution() > m_rigidObjects[j].getRestitution()) ? m_rigidObjects[i].getRestitution() :
//                                                                                              m_rigidObjects[i].getRestitution();

//        //calculate impulse scalar
//        float j = -(1+e) * velAlongNormal;
//        j /= 1 / m_rigidObjects[i].getMass() + 1 / m_rigidObjects[j].getMass();

//        //Impulse

//        ngl::Vec3 impulse = j * direction;
    //    m_rigidObjects[i].setVelocity(m_rigidObjects[i].getVelocity() - 1 / m_rigidObjects[i].getMass() * impulse);
    //    m_rigidObjects[j].setVelocity(m_rigidObjects[j].getVelocity() + 1 / m_rigidObjects[j].getMass() * impulse);


       // m_rigidObjects[i].setVelocity(ngl::Vec3(newVel_ix, newVel_iy, newVel_iz));
       // m_rigidObjects[j].setVelocity(ngl::Vec3(newVel_jx, newVel_jy, newVel_jz));

        m_rigidObjects[i].setVelocity(newVel_i);
        m_rigidObjects[j].setVelocity(newVel_j);







      }

    //  ngl::Vec3 force = m_rigidObjects[i].attractForce(m_rigidObjects[j]);
    }
  }
}

void PhysicsEngine::checkGroundWallCollision()
{
  ///@brief Collision response based on objects intersecting the ground plane.
  for(auto& i : m_rigidObjects)
  {
    if((i.getPosition().m_y - i.transformCollider().getSize().m_y) < m_groundPlane_y || (i.getPosition().m_y - i.transformCollider().getSize().m_y) > 100)
    {
      ngl::Vec3 normal = ngl::Vec3(0.0,1.0,0.0);

      i.setVelocity(ngl::Vec3((i.getVelocity().reflect(normal))/(i.getMass())));
      i.setPosition(i.getPosition() + ngl::Vec3(0.0, -m_gravity.m_y/13000,0.0)); // Simple hack to account for precision errors to help
                                                                                  //prevent objects sinking into the ground
//      Linear projection - stops objects sinking into ground plane due to gravity floating point errors
//      const float percent = 0.2;
//      const float slop = 0.01;
//      ngl::Vec3 correction = ngl::Vec3(0.0,penetrationDepth,0.0) / (1/(i.getMass()) * percent * normal);
//      i.setPosition(i.getPosition() + 1/(i.getMass()) * correction);
    }
    if((i.getPosition().m_x + i.transformCollider().getSize().m_x) > 100 || (i.getPosition().m_x - i.transformCollider().getSize().m_x) < -100)
    {

      i.setVelocity(ngl::Vec3(i.getVelocity().reflect(ngl::Vec3(1.0,0.0,0.0))/(i.getMass())));
       i.setPosition(i.getPosition() + ngl::Vec3(-m_gravity.m_y/13000, 0.0, 0.0));
    }
    if((i.getPosition().m_z + i.transformCollider().getSize().m_z) > 100 || (i.getPosition().m_z - i.transformCollider().getSize().m_z) < -100)
    {
      i.setVelocity(ngl::Vec3(i.getVelocity().reflect(ngl::Vec3(0.0,0.0,1.0))/(i.getMass())));
      i.setPosition(i.getPosition() + ngl::Vec3(0.0, 0.0, -m_gravity.m_y/13000));
    }
  }
}


void PhysicsEngine::updatePhysics(float _time)
{
  // std::cout<<"updating\n";
  for(auto& i : m_rigidObjects)
  {
    i.integrate(_time, applyWorldForces());


  }
  handleCollisions();
  if(m_boundingAreaOn)
    checkGroundWallCollision();
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

