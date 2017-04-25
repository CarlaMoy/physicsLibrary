#ifndef RIGID_BODY_FACTORY_H_
#define RIGID_BODY_FACTORY_H_

#include "rigidBody.h"

/// @file rigidBodyFactory.h
/// @brief A factory class for creating rigid bodies
/// @author Carla Moy
/// @version 1.0
/// @date 10/04/17
/// @class RigidBodyFactory
/// @brief Creates rigid body object and returns it to the Physics Engine class

class PhysicsEngine;

class RigidBodyFactory
{
public:
    /// @brief Create a rigid body and return
    /// @brief[in] _type the type of rigid body to create
    /// @brief[in] _pos the type of rigid body initially
    /// @brief[in] _dir the type of rigid body initially
    /// @brief[in] _colour the colour of rigid body
    /// @brief[in] _shaderName the name of the shader to use when rendering

    RigidBody *CreateRigidBody(
                                RigidBodyType _type,
                                ngl::Vec3 _pos,
                                ngl::Vec3 _dir,
                                ngl::Colour _colour,
                                const std::string &_shaderName,
                                PhysicsEngine *_parent
                                );
};


#endif
