#ifndef SPHERE_H_
#define SPHERE_H_

/// @file sphere.h
/// @brief A Sphere class for rigid body
/// @class RigidBody
/// @brief this inherits from the base rigid body class and draws a sphere

#include "rigidBody.h"

class Sphere : public RigidBody
{
public:
    /// @brief constructor called by the child classes
    /// @param[in] _pos the position of the particle
    /// @param[in] _dir the direction of the particle
    /// @param[in] _colour the colour of the particle
    /// @param[in] _shaderName the name of the shader to use
    /// @param[in] _parent the parent (Physics Engine used to query global values)

    Sphere(
            ngl::Vec3 _pos,
            ngl::Vec3 _dir,
            ngl::Colour _colour,
            const std::string &_shaderName,
            Emitter *_parent
            );
    ///@param dtor
    virtual ~Sphere();
    /// @brief draw the sphere
    virtual void draw() const;
    /// @brief update the sphere
    virtual void update();
    /// @brief accessor to get the rigid body type
    /// @returns the rigid body type
    virtual inline RigidBodyType getType()const {return m_type;}

private:
    /// @brief the current radius for the sphere
    float m_radius;
    /// @brief what type of particle this is
    const static RigidBodyType m_type=RigidBodyType::SPHERE;

};



#endif
