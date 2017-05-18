#ifndef RIGIDBODY_H
#define RIGIDBODY_H

//#include <glm/glm.hpp>
#include <ngl/Camera.h>
#include <ngl/Colour.h>
#include <ngl/Transformation.h>
#include <ngl/ShaderLib.h>
#include "collider.h"
#include <ngl/Vec4.h>
#include "spatialPartition.h"

///@file rigidBody.h
///@brief Rigid Body class used to instantiate rigid bodies either of AABB or sphere collider types. This class creates
/// the rigid body entities for the physics engine.
///@author Carla Moy
///@class RigidBody

class RigidBody
{
  friend class SpatialGrid;

public:
    ///@brief Constructor for rigid body
    ///@param collider Collider for the rigid body (Either sphere or AABB)
    ///@param velocity Vector for initial velocity
    ///@param colour Vector for colour
    ///@param mass Float for mass
    ///@param frictionCoeff Float for the coefficient of friction
    RigidBody(Collider* collider, const ngl::Vec3& velocity, const ngl::Vec3 &colour, float mass, float frictionCoeff) :
                                                            m_position(collider->getCentre()),
                                                            m_oldPosition(collider->getCentre()),
                                                            m_velocity(velocity),
                                                            m_colour(colour),
                                                            m_acceleration(ngl::Vec3(0.0,0.0,0.0)),
                                                            m_mass(mass),
                                                            m_frictionCoeff(frictionCoeff),
                                                            m_collider(collider){}
    ///@brief Copy constructor for RigidBody
    ///@param other The other rigid body to copy
    RigidBody(const RigidBody& other)=default;
    ///@brief Destructor for RigidBody
    ~RigidBody(){}

    ///@brief Method to integrate the rigid bodies' positions based on velocity, forces and acceleration
    ///@param delta The timestep for the simulation
    ///@param force The force to apply taken from the PhysicsEngine class
    void integrate(float delta, ngl::Vec3 force);

    ///@brief Method to draw rigid body
    ///@param _globalTx The matrix for the camera transforms
    ///@param _cam The camera to use, taken from NGLScene
    ///@param _shaderName The name of the shader used to colour and light the objects
    void drawRigidBody(const ngl::Mat4 &_globalTx, ngl::Camera *_cam, const std::string _shaderName) const;
    ///@brief Method for attract force between two rigid body objects (Unimplemented in engine at the moment)
    ngl::Vec3 attractForce(const RigidBody &_object);

    ///@brief Method to get postion
    const ngl::Vec3& getPosition() const {return m_position;}
    ///@brief Method to get velocity
    const ngl::Vec3& getVelocity() const {return m_velocity;}
    ///@brief Method to get colour
    const ngl::Vec3& getColour() const {return m_colour;}
    ///@brief Method to get mass
    const float& getMass() const {return m_mass;}
    ///@brief Method to get friction coefficient
    const float& getfrictionCoeff() const {return m_frictionCoeff;}

    ///@brief Method to update and get the collider used.
    const Collider& transformCollider();

    ///@brief Method to set the position
    ///@param position Vector for setting the new postion
    void setPosition(ngl::Vec3 position) {m_position = position;}
    ///@brief Method to set the velocity
    ///@param velocity Vector for setting the new velocity
    void setVelocity(ngl::Vec3 velocity) {m_velocity = velocity;}
    ///@brief Method to set the colour
    ///@param colour Vector for setting the new colour
    void setColour(ngl::Vec3 newColour) {m_colour = newColour;}




private:
    ///@brief Vector for position of object
    ngl::Vec3 m_position;
    ///@brief Vector for previous position of object
    ngl::Vec3 m_oldPosition;
    ///@brief Vector for direction of object
    ngl::Vec3 m_direction;
    ///@brief Vector for velocity of object
    ngl::Vec3 m_velocity;
    ///@brief Vector for colour of object
    ngl::Vec3 m_colour;
    ///@brief Vector for acceleration of object
    ngl::Vec3 m_acceleration;
    ///@brief Vector for previous acceleration of object
    ngl::Vec3 m_oldAcceleration;
    ///@brief Vector for average acceleration of object
    ngl::Vec3 m_avg_acceleration;
    ///@brief Vector for friction of object
    ngl::Vec3 m_friction;
    ///@brief Vector for drag of object
    //ngl::Vec3 m_drag;

    ///@brief Float for mass of object
    float m_mass;
    ///@brief Float for coefficient of friction of object
    float m_frictionCoeff;

    ///@brief Pointer to collider for accessing AABB or sphere colliders
    std::shared_ptr<Collider> m_collider;


    ///@brief Method to calculate friction
    ngl::Vec3 calculateFriction();
    ///@brief Method to calculate drag
    ngl::Vec3 calculateDrag();
    ///@brief Method for applying per object based forces such as friction
    ngl::Vec3 applyObjectForces();



};


#endif // RIGIDBODY_H
