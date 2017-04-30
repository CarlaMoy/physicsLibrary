#ifndef RIGIDBODY_H
#define RIGIDBODY_H

//#include <glm/glm.hpp>
#include <ngl/Camera.h>
#include <ngl/Colour.h>
#include <ngl/Transformation.h>
#include <ngl/ShaderLib.h>
#include "collider.h"
#include <ngl/Vec4.h>
#include "rigidBodyTypeInfo.h"



class PhysicsEngine;

class RigidBody
{
public:
    RigidBody(Collider* collider, const ngl::Vec3& velocity, const ngl::Vec3 colour, float mass) :
                                                            m_position(collider->getCentre()),
                                                            m_oldPosition(collider->getCentre()),
                                                            m_velocity(velocity),
                                                            m_colour(colour),
                                                            m_acceleration(ngl::Vec3(0.0,0.0,0.0)),
                                                            m_mass(mass),
                                                            m_collider(collider){}
    RigidBody(const RigidBody& other);
    RigidBody operator=(RigidBody other);
    virtual ~RigidBody();

    void integrate(float delta);
    /// @brief Method to update rigid body
   // virtual void updateRigidBody(ngl::Transformation &_transform,const ngl::Mat4 &_globalTx, ngl::Camera *_cam, float _delta ) const;
    /// @brief Method to draw rigid body
    virtual void drawRigidBody(const ngl::Mat4 &_globalTx, ngl::Camera *_cam, const std::string _shaderName) const;
                              //ngl::Transformation &_transform,
    const ngl::Vec3& getPosition() const {return m_position;}
    const ngl::Vec3& getVelocity() const {return m_velocity;}
    const ngl::Vec3& getColour() const {return m_colour;}
   // float getRadius() const {return m_radius;}
    const Collider& getCollider();
    //virtual RigidBodyType getType() const{};


    void setPosition(const ngl::Vec3& position) {m_position = position;}
    void setVelocity(const ngl::Vec3& velocity) {m_velocity = velocity;}
    void setColour(const ngl::Vec3& colour) {m_colour = colour;}


   // mutable BoundingSphere m_boundingSphere;
private:
    ngl::Vec3 m_position;
    ngl::Vec3 m_oldPosition;
    ngl::Vec3 m_direction;
    ngl::Vec3 m_velocity;
    ngl::Vec3 m_colour;
    ngl::Vec3 m_acceleration;
    ngl::Vec3 m_gravity = ngl::Vec3(0.0,-9.8,0.0);

    float m_mass;
    bool m_isDynamic;
  //  float m_radius;

    Collider* m_collider;
 //   PhysicsEngine *m_parent;

};


#endif // RIGIDBODY_H
