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
#include "spatialPartition.h"

///@file aabb.h
///@brief AABB Class, child class of Collider for generating and checking AABB based collision.
///@author Carla Moy
///@class AABB

class RigidBody
{
  friend class SpatialGrid;

public:
    RigidBody(Collider* collider, const ngl::Vec3& velocity, const ngl::Vec3 &colour, float mass, float frictionCoeff) :
                                                            m_position(collider->getCentre()),
                                                            m_oldPosition(collider->getCentre()),
                                                            m_velocity(velocity),
                                                            m_colour(colour),
                                                            m_acceleration(ngl::Vec3(0.0,0.0,0.0)),
                                                            m_mass(mass),
                                                            m_frictionCoeff(frictionCoeff),
                                                            m_collider(collider){}
    RigidBody(const RigidBody& other)=default;
 //   RigidBody operator=(RigidBody other);
    ~RigidBody();

    void integrate(float delta, ngl::Vec3 force);
    /// @brief Method to update rigid body
   // virtual void updateRigidBody(ngl::Transformation &_transform,const ngl::Mat4 &_globalTx, ngl::Camera *_cam, float _delta ) const;
    /// @brief Method to draw rigid body
    void drawRigidBody(const ngl::Mat4 &_globalTx, ngl::Camera *_cam, const std::string _shaderName, ngl::Vec3 _colour) const;
    ngl::Vec3 attractForce(const RigidBody &_object);

                              //ngl::Transformation &_transform,
    const ngl::Vec3& getPosition() const {return m_position;}
    const ngl::Vec3& getVelocity() const {return m_velocity;}
    const ngl::Vec3& getColour() const {return m_colour;}
    const float& getMass() const {return m_mass;}
    const float& getfrictionCoeff() const {return m_frictionCoeff;}
    const Collider& transformCollider();
    //virtual RigidBodyType getType() const{};


    void setPosition(ngl::Vec3 position) {m_position = position;}
    void setVelocity(ngl::Vec3 velocity) {m_velocity = velocity;}
    void setColour(ngl::Vec3 newColour) {m_colour = newColour;}




private:
    ngl::Vec3 m_position;
    ngl::Vec3 m_oldPosition;
    ngl::Vec3 m_direction;
    ngl::Vec3 m_velocity;
    ngl::Vec3 m_colour;
    ngl::Vec3 m_acceleration;
    ngl::Vec3 m_oldAcceleration;
    ngl::Vec3 m_avg_acceleration;
    ngl::Vec3 m_friction;
    ngl::Vec3 m_drag;


    float m_mass;
    float m_frictionCoeff;

    GLuint m_ID;
   // bool m_isDynamic;

    Collider* m_collider;
 //   std::unique_ptr<SpatialGrid> m_grid;

   // std::unique_ptr<RigidBody> m_prev;
   // std::unique_ptr<RigidBody> m_next;

    //PhysicsEngine


    ngl::Vec3 calculateFriction();
    ngl::Vec3 calculateDrag();
    ngl::Vec3 applyObjectForces();



};


#endif // RIGIDBODY_H
