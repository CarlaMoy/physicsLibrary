#ifndef BOUNDING_SPHERE_H
#define BOUNDING_SPHERE_H

#include <glm/glm.hpp>
#include "intersectdata.h"
#include "collider.h"
#include <ngl/NGLInit.h>

class BoundingSphere : public Collider
{
public:
    BoundingSphere(const ngl::Vec3& centre, float radius) : Collider(Collider::TYPE_SPHERE), m_centre(centre), m_radius(radius){}

    IntersectData intersectBoundingSphere(const BoundingSphere& other) const;

    virtual void transform(const ngl::Vec3& translation);
    virtual ngl::Vec3 getCentre() const {return m_centre;}

    float getRadius() const { return m_radius; }
private:
    ngl::Vec3 m_centre;
    float m_radius;
};

#endif