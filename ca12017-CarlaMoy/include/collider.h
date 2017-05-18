#ifndef COLLIDER_H
#define COLLIDER_H

#include <glm/glm.hpp>
#include "intersectdata.h"
#include <ngl/NGLInit.h>

///@file collider.h
///@brief Class Collider. Has to be overwritten by a child class, corresponding to a collider type for implementation.
/// This method was inspired by the implementation by BennyQBD at github via :
/// https://github.com/BennyQBD/3DEngineCpp/tree/7e0022e0d0e253f50ee14a00abcf095fa8fa667f/src/physics
///@author Carla Moy
///@class Collider
class Collider
{
public:
    ///@brief Enum for the different types of rigid body colliders
    enum{
        TYPE_SPHERE,
        TYPE_AABB,
        //TYPE_PLANE
    };

    ///@brief Constructor for the Collider
    ///@param type The type to implement (Either AABB or SPHERE)
    Collider(int type) : m_type(type){}

    ///@brief Destructor for the Collider
    ~Collider(){}

    ///@brief Method for checking and resolving the type of collision case
    /// (Whether AABB-AABB, sphere-sphere or AABB-sphere)
    ///@param other The other collider to compare with
    IntersectData intersect(const Collider& other) const;
   // virtual IntersectData intersectGroundPlane();

    ///@brief Method for updating collider position for collision checks (must be overriden by child)
    ///@param translation The amount to move the collider
    virtual void transform(const ngl::Vec3& translation) = 0;
    ///@brief Method to get centre (must be overriden by child)
    virtual ngl::Vec3 getCentre() const = 0;
    ///@brief Method to get size (must be overriden by child)
    virtual ngl::Vec3 getSize() const = 0;
    ///@brief Method to draw object (must be overriden by child)
    virtual void drawObject() = 0;
    ///@brief Method to return type of collider (AABB or SPHERE)
    int getType() const {return m_type;}

private:
    ///@brief Int storing the type of collider
    int m_type;
};

#endif // COLLIDER_H
