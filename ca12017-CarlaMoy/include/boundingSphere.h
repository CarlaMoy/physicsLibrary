#ifndef BOUNDING_SPHERE_H
#define BOUNDING_SPHERE_H

#include <glm/glm.hpp>
#include "intersectdata.h"
#include "collider.h"
#include "aabb.h"
#include <ngl/NGLInit.h>

///@file boundingSphere.h
///@brief Bounding Sphere Class, child class of Collider for generating and checking bounding sphere based collision.
///@author Carla Moy
///@class BoundingSphere
class AABB;

class BoundingSphere : public Collider
{
public:
    ///@brief Constructor for Bounding Sphere
    ///@param centre Initial centre
    ///@param radius Radius of sphere
    BoundingSphere(const ngl::Vec3& centre, float radius) : Collider(Collider::TYPE_SPHERE), m_centre(centre), m_radius(radius){}

    ///@brief Destructor for sphere
    ~BoundingSphere(){}

    ///@brief Collision check for sphere-sphere collision
    ///@param other The other sphere to compare to
    IntersectData sphereIntersectBoundingSphere(const BoundingSphere& other) const;
    ///@brief Collision check for sphere-AABB
    ///@param other The AABB to compare to
    IntersectData sphereIntersectAABB(const AABB& other) const;

    ///@brief Translates collider to new position,
    ///used in RigidBody.cpp for updating position for collision checks.
    ///@param translation The amount to translate, given by change in position each frame.
    void transform(const ngl::Vec3& translation) override;

    ///@brief returns the object centre
    ngl::Vec3 getCentre() const override {return m_centre;}
    ///@brief returns the object size
    ngl::Vec3 getSize() const override {return ngl::Vec3(m_radius, m_radius, m_radius);}
    ///@brief returns the object radius
    float getRadius() const { return m_radius; }

    ///@brief Method to draw sphere
    void drawObject();

private:
    ///@brief Vector for the centre of the object
    ngl::Vec3 m_centre;
    ///@brief float for the radius
    float m_radius;
};

#endif
