#include "rigidBody.h"
#include "boundingSphere.h"
#include <iostream>
#include <cassert>
#include <cstring>
#include <ngl/NGLStream.h>



void RigidBody::integrate(float delta, ngl::Vec3 force)
{
  //check that mass is not divided by a number less than 1 to prevent acceleration value being too large
  if(m_mass <= 1.0)
  {
    m_mass += 1.0;
  }
  //Method based on verlet integration
  //Modified from : https://www.gamedev.net/resources/_/technical/math-and-physics/a-verlet-based-approach-for-2d-game-physics-r2714
  force += applyObjectForces();
  m_oldAcceleration = m_acceleration;
  m_position += m_velocity * delta + (0.5 * m_oldAcceleration * delta * delta);
  m_acceleration = force * delta / m_mass;
  m_avg_acceleration = (m_oldAcceleration + m_acceleration) / 2;
  m_velocity += m_avg_acceleration * delta;

}


//Code for friction, drag and attractForce modified from : http://natureofcode.com/book/chapter-2-forces/
ngl::Vec3 RigidBody::calculateFriction()
{
  ngl::Vec3 friction = -m_velocity;
  //friction.normalize();
  friction *= m_frictionCoeff;
  return friction;
}


ngl::Vec3 RigidBody::calculateDrag()
{
  float speed = m_velocity.length();
  float dragMagnitude = speed * speed * m_frictionCoeff; //drag coefficient and friction coefficient are the same value for now
  ngl::Vec3 drag = -m_velocity;
  drag *= dragMagnitude;
  return drag;
}


ngl::Vec3 RigidBody::applyObjectForces()
{
  return (calculateFriction() + calculateDrag())*0.005; //reduce effect
}


//Not yet implemented
ngl::Vec3 RigidBody::attractForce(const RigidBody &_object)
{
  ngl::Vec3 force = m_position - _object.getPosition();
  float distance = force.length();
  force.normalize();

  float strength = (1 * m_mass * _object.getMass()) / (distance * distance);
  force *= strength;
  return force;
}


const Collider& RigidBody::transformCollider()
{
  ngl::Vec3 translation = m_position - m_oldPosition;
  m_oldPosition = m_position;
  m_collider->transform(translation);

  return *m_collider;
}


void RigidBody::drawRigidBody(const ngl::Mat4 &_globalTx, ngl::Camera *_cam, const std::string _shaderName) const
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();

  ngl::Transformation transform;
  shader->use(_shaderName);
  transform.reset();
  {
    transform.setPosition( m_position.m_x,m_position.m_y,m_position.m_z);
    transform.setScale(m_collider->getSize());

    ngl::Mat4 MV;
    ngl::Mat4 MVP;
    ngl::Mat3 normalMatrix;
    ngl::Mat4 M;
    M=transform.getMatrix()*_globalTx;
    MV=M*_cam->getViewMatrix() ;
    MVP=MV*_cam->getProjectionMatrix();
    normalMatrix=MV;
    normalMatrix.inverse();
    shader->setShaderParamFromMat4("MVP",MVP);
    shader->setShaderParamFromMat3("normalMatrix",normalMatrix);
    shader->setShaderParam3f("Colour", m_colour.m_r, m_colour.m_g, m_colour.m_b);

    m_collider->drawObject();

  }
}





