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
    BoundingSphere(const ngl::Vec3& centre, float radius) : Collider(Collider::TYPE_SPHERE), m_centre(centre), m_radius(radius){}
    ~BoundingSphere(){}

    IntersectData sphereIntersectBoundingSphere(const BoundingSphere& other) const;
    IntersectData sphereIntersectAABB(const AABB& other) const;


    IntersectData intersectGroundPlane();
    void transform(const ngl::Vec3& translation) override;
    ngl::Vec3 getCentre() const override {return m_centre;}
    ngl::Vec3 getSize() const override {return ngl::Vec3(m_radius, m_radius, m_radius);} //get diameter
    float getRadius() const { return m_radius; }

private:
    ngl::Vec3 m_centre;
    float m_radius;
};

#endif
