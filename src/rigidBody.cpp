#include "rigidBody.h"
#include "boundingSphere.h"
#include <iostream>
#include <cassert>
#include <cstring>
#include <ngl/NGLStream.h>

RigidBody::RigidBody(const RigidBody& other) :
  m_position(other.m_position),
  m_oldPosition(other.m_oldPosition),
  m_velocity(other.m_velocity),
  m_collider(other.m_collider)
{
  //m_collider->AddReference();
}

RigidBody RigidBody::operator=(RigidBody other)
{
  //Implemented using the copy/swap idiom.
  char* temp[sizeof(RigidBody)/sizeof(char)];
  memcpy(temp, this, sizeof(RigidBody));
  memcpy(this, &other, sizeof(RigidBody));
  memcpy(&other, temp, sizeof(RigidBody));
}

RigidBody::~RigidBody(){}


void RigidBody::integrate(float delta)
{
  m_position += m_velocity * delta;
  m_velocity += m_gravity * delta;
  std::cout<<m_velocity<<" velocity\n";
  std::cout<<m_gravity<<" gravity\n";
}


const Collider& RigidBody::getCollider()
{
  ngl::Vec3 translation = m_position - m_oldPosition;
  m_oldPosition = m_position;
  m_collider->transform(translation);

  return *m_collider;
}

void RigidBody::drawRigidBody(const ngl::Mat4 &_globalTx, ngl::Camera *_cam, const std::string _shaderName) const
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
  ngl::Transformation transform;
  shader->use(_shaderName);
  transform.reset();
  {
    transform.setPosition(m_position);
    transform.setScale(m_collider->getSize()*2); // *2 to get diameter instead of radius

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
    shader->setShaderParam3f("Colour",m_colour.m_r, m_colour.m_g, m_colour.m_b);

    if(m_collider->getType() == m_collider->TYPE_SPHERE)
      prim->draw("sphere");
    else if(m_collider->getType() == m_collider->TYPE_AABB)
      prim->draw("cube");
  }
}

/*void RigidBody::updateRigidBody(ngl::Transformation &_transform,const ngl::Mat4 &_globalTx, ngl::Camera *_cam, float _delta ) const
{
    integrate(_delta);
    getCollider();
    drawRigidBody(_transform, _globalTx, _cam);
}*/




