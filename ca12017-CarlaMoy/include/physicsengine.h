#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include "rigidBody.h"
#include <glm/glm.hpp>
#include <vector>
#include <ngl/SimpleVAO.h>
#include <memory>

///@file physicsengine.h
///@brief The physics engine class is a singleton class for the physics world which updates all rigid bodies, applies world
/// forces and handles all the rigid bodies' collisions.
///@author Carla Moy
///@class PhysicsEngine

class PhysicsEngine
{
public:
    ///@brief Destructor for Physics Engine
    ~PhysicsEngine(){}

    ///@brief Method to add rigid body object
    ///@param object The RigidBody object to create
    void addObject(const RigidBody& object);
    ///@brief Method to get a specific rigid body from the array
    ///@param index The index to get the object within the std::vector array
    RigidBody getObject(unsigned int index) const;
    ///@brief Method to get the number of rigid bodies created
    unsigned int getNumObjects() const;

    ///@brief Method to handle collisions between objects
    void handleCollisions();
    ///@brief Method to check collisions with ground and walls for each object
    void checkGroundWallCollision();

    ///@brief Method for updating all rigid bodies and checking collisions each frame
    ///@param _time The timestep for updating the rigid bodies
    void updatePhysics(float _time);
    ///@brief Method to draw each object to screen
    ///@param _globalTx The matrix for the camera transforms
    ///@param _cam The camera to use, taken from NGLScene
    ///@param _shaderName The name of the shader used to colour and light the objects
    void drawPhysics(const ngl::Mat4 &_globalTx, ngl::Camera *_cam, const std::string _shaderName);

    ///@brief Method for setting the gravity
    ///@param _value The value for setting the amount of gravity
    void setGravity(float _value){m_gravity.m_y = _value;}
    ///@brief Method for setting the restitution for elastic or inelastic collisions.
    ///@param _restitution The value for the restitution
    void setRestitutionCoeff(float _restitution) {m_restitutionCoeff = _restitution;}
    ///@brief Method to change whether bounding area is active
    ///@param _choice Boolean to turn on or off bounding area
    void setBoundingArea(bool _choice) {m_boundingAreaOn = _choice;}

    ///@brief Method to apply forces such as gravity and wind
    ngl::Vec3 applyWorldForces();
    ///@brief Method to add wind
    ///param _amount The amount of wind to add
    void addWind(ngl::Vec3 _amount);
    ///@brief Method to reset forces
    void resetForces();
    ///@brief Method to remove all rigid body objects
    void resetWorld() {m_rigidObjects.clear();}


    ///@brief instance for the Physics engine singleton
    static PhysicsEngine* instance();

private:

    ///@brief std::vector to store rigid bodies
    std::vector<RigidBody> m_rigidObjects;

    ///@brief The boolean for determining the state of the bounding area
    bool m_boundingAreaOn = true;
    ///@brief float for the location of the ground plane
    //float m_groundPlane_y = 0.0f;
    ///@brief Vector for the gravity
    ngl::Vec3 m_gravity;
    ///@brief Vector for the wind
    ngl::Vec3 m_wind;
    ///@brief Float for the restitution coefficient
    float m_restitutionCoeff = 0.5;

    ///@brief The pointer for the singleton instance
    static PhysicsEngine *s_instance;

    ///@brief Constructor for the physics engine (Private for singleton)
    PhysicsEngine(){}
};

#endif // PHYSICSENGINE_H
