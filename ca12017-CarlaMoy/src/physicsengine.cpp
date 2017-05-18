#include "physicsengine.h"
#include "boundingSphere.h"
#include <iostream>
#include <ngl/NGLInit.h>
#include <ngl/VAOFactory.h>
#include <ngl/SimpleVAO.h>
#include <ngl/Util.h>
#include <ngl/NGLStream.h>
#include "rigidBody.h"

PhysicsEngine* PhysicsEngine::s_instance = 0;

PhysicsEngine* PhysicsEngine::instance()
{
  if(!s_instance)
    s_instance = new PhysicsEngine;
  return s_instance;
}



void PhysicsEngine::addObject(const RigidBody& object)
{
  m_rigidObjects.push_back(object);


}

RigidBody PhysicsEngine::getObject(unsigned int index) const
{
    if(index <= m_rigidObjects.size())
        return m_rigidObjects[index];
    else
      std::cerr << "Error: getObject(index) is out of range.\n";
      exit(1);
}



unsigned int PhysicsEngine::getNumObjects() const
{
    return (unsigned int) m_rigidObjects.size();
}



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
  }
}



void PhysicsEngine::handleCollisions()
{
  //Brute force approach. This method could be improved with the spatial grid in future.
  for(unsigned int i = 0; i < m_rigidObjects.size(); ++i)
  {
    for(unsigned int j = i+1; j < m_rigidObjects.size(); ++j)
    {
      // if(i==j) continue; Collisions react differently when implementation is i = 0, j = 0.
      // Gets whether objects intersect and the direction of intersection between BoundingSphere-BoundingSphere,
      // BoundingSphere-AABB, AABB-AABB.
      IntersectData intersectData = m_rigidObjects[i].transformCollider().intersect(m_rigidObjects[j].transformCollider());


      // Collision response based on intersection of two dynamic rigid bodies
      if(intersectData.GetDoesIntersect())
      {
        ngl::Vec3 direction = intersectData.getDirection();
        ngl::Vec3 relativeVel = m_rigidObjects[j].getVelocity() - m_rigidObjects[i].getVelocity();
        float velAlongNormal = relativeVel.dot(direction);

        //Do not resolve if velocities are moving away
        if(velAlongNormal > 0)
          continue;

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

        m_rigidObjects[i].setVelocity(newVel_i);
        m_rigidObjects[j].setVelocity(newVel_j);

        m_rigidObjects[i].setPosition(m_rigidObjects[i].getPosition() + ngl::Vec3(0.0, -m_gravity.m_y/600,0.0));
        m_rigidObjects[j].setPosition(m_rigidObjects[j].getPosition() + ngl::Vec3(0.0, -m_gravity.m_y/600,0.0));

//---------------------------------------------------------------------------------------------------------------------------------//
//         Another method for implementing collision response based on impulse (Not yet implemented due to inaccuracies)
//        //calculate restitution
//        float e = (m_rigidObjects[i].getRestitution() > m_rigidObjects[j].getRestitution()) ? m_rigidObjects[i].getRestitution() :
//                                                                                              m_rigidObjects[i].getRestitution();
//        //calculate impulse scalar
//        float j = -(1+e) * velAlongNormal;
//        j /= 1 / m_rigidObjects[i].getMass() + 1 / m_rigidObjects[j].getMass();
//
//        //Impulse
//        ngl::Vec3 impulse = j * direction;
//        m_rigidObjects[i].setVelocity(m_rigidObjects[i].getVelocity() - 1 / m_rigidObjects[i].getMass() * impulse);
//        m_rigidObjects[j].setVelocity(m_rigidObjects[j].getVelocity() + 1 / m_rigidObjects[j].getMass() * impulse);
//
//        m_rigidObjects[i].setVelocity(ngl::Vec3(newVel_ix, newVel_iy, newVel_iz));
//        m_rigidObjects[j].setVelocity(ngl::Vec3(newVel_jx, newVel_jy, newVel_jz));
//---------------------------------------------------------------------------------------------------------------------------------//
      }
    }
  }
}



void PhysicsEngine::checkGroundWallCollision()
{
  // Collision response based on objects intersecting the ground plane.
  for(auto& i : m_rigidObjects)
  {
    //if the object goes out of bounds in the y axis
    if((i.getPosition().m_y - i.transformCollider().getSize().m_y/2) < 0 ||(i.getPosition().m_y + i.transformCollider().getSize().m_y) > 100)
    {
      ngl::Vec3 normal = ngl::Vec3(0.0,1.0,0.0);

      //check that mass is an accepted value
      if(i.getMass() >= 0.0)
        //reflect direction and lose some energy based on the mass of the object
        i.setVelocity(ngl::Vec3((i.getVelocity().reflect(normal))/(i.getMass())));
        // Simple hack to account for precision errors to help
        //prevent objects sinking into the ground
        i.setPosition(i.getPosition() + ngl::Vec3(0.0, -m_gravity.m_y/13000,0.0));

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//      Another solution to ground plane sinking problem (Not yet implemented due to inaccuracies)
//      Modified from : https://gamedevelopment.tutsplus.com/tutorials/how-to-create-a-custom-2d-physics-engine-the-basics-and-impulse-resolution--gamedev-6331
//      Linear projection - stops objects sinking into ground plane due to gravity floating point errors
//      const float percent = 0.2;
//      const float slop = 0.01;
//      ngl::Vec3 correction = ngl::Vec3(0.0,penetrationDepth,0.0) / (1/(i.getMass()) * percent * normal);
//      i.setPosition(i.getPosition() + 1/(i.getMass()) * correction);
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
    }
    //if the object goes out of bounds in the x axis
    if((i.getPosition().m_x + i.transformCollider().getSize().m_x) > 100 || (i.getPosition().m_x - i.transformCollider().getSize().m_x) < -100)
    {
      if(i.getMass() >= 0.0)
        i.setVelocity(ngl::Vec3(i.getVelocity().reflect(ngl::Vec3(1.0,0.0,0.0))/(i.getMass())));
      i.setPosition(i.getPosition() + ngl::Vec3(-m_gravity.m_y/13000, 0.0, 0.0));
    }
    //if the object goes out of bounds in the z axis
    if((i.getPosition().m_z + i.transformCollider().getSize().m_z) > 100 || (i.getPosition().m_z - i.transformCollider().getSize().m_z) < -100)
    {
      if(i.getMass() >= 0.0)
        i.setVelocity(ngl::Vec3(i.getVelocity().reflect(ngl::Vec3(0.0,0.0,1.0))/(i.getMass())));
      i.setPosition(i.getPosition() + ngl::Vec3(0.0, 0.0, -m_gravity.m_y/13000));
    }
  }
}



void PhysicsEngine::updatePhysics(float _time)
{
  for(auto& i : m_rigidObjects)
  {
    i.integrate(_time, applyWorldForces());
  }

  handleCollisions();

  if(m_boundingAreaOn)
    checkGroundWallCollision();
}



void PhysicsEngine::drawPhysics(const ngl::Mat4 &_globalTx, ngl::Camera *_cam, const std::string _shaderName)
{
  for(auto& i : m_rigidObjects)
  {
    i.drawRigidBody(_globalTx, _cam, _shaderName);
  }
}



