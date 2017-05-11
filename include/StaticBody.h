#ifndef STATICBODY_H
#define STATICBODY_H

//#include <glm/glm.hpp>
#include <ngl/Camera.h>
#include <ngl/Colour.h>
#include <ngl/Transformation.h>
#include <ngl/ShaderLib.h>
#include "collider.h"
#include <ngl/Vec4.h>
#include "rigidBodyTypeInfo.h"



class PhysicsEngine;

class StaticBody
{
public:
    StaticBody(Collider* collider, const ngl::Vec3 colour) :
                                                            m_position(collider->getCentre()), //could initialise position once instead of in
                                                            m_colour(colour),
                                                            m_collider(collider){}
  //  StaticBody(const StaticBody& other);
    virtual ~StaticBody(){}

    virtual void drawStaticBody(const ngl::Mat4 &_globalTx, ngl::Camera *_cam, const std::string _shaderName) const;
                              //ngl::Transformation &_transform,
    const ngl::Vec3& getPosition() const {return m_position;}
    const ngl::Vec3& getColour() const {return m_colour;}
    const Collider& getCollider() {return *m_collider;}
    //virtual RigidBodyType getType() const{};


    void setColour(const ngl::Vec3& colour) {m_colour = colour;}


private:
    ngl::Vec3 m_position;
    ngl::Vec3 m_colour;
    float m_mass;
    Collider* m_collider;


};


#endif // STATICBODY_H
