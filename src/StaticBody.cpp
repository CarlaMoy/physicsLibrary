#include "StaticBody.h"


void StaticBody::drawStaticBody(const ngl::Mat4 &_globalTx, ngl::Camera *_cam, const std::string _shaderName) const
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
  ngl::Transformation transform;
  shader->use(_shaderName);
  transform.reset();
  {
    transform.setPosition(m_position);
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
    shader->setShaderParam3f("Colour",m_colour.m_r, m_colour.m_g, m_colour.m_b);

    switch(m_collider->getType())
    {
      case m_collider->TYPE_PLANE :
        prim->draw("plane"); break;
    }
  }
}
