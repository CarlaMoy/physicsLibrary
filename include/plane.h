/*#ifndef PLANE_H
#define PLANE_H

#include <glm/glm.hpp>
#include "boundingSphere.h"
#include "aabb.h"

class Plane : public Collider
{
public:
    Plane(const ngl::Vec3& normal, float distance) : Collider(Collider::TYPE_PLANE),
                                                                                m_normal(normal),
                                                                                m_distance(distance){} //possibly add position

    Plane normalised() const;

    IntersectData intersectSphere(const BoundingSphere& other) const;
    IntersectData intersectAABB(const AABB& other) const;

    ngl::Vec3 getCentre() const {return m_normal;} //might be wrong
    ngl::Vec3 getSize() const {return ngl::Vec3(m_distance, m_distance, m_distance);}

    const ngl::Vec3& getNormal() const {return m_normal;}
    float getDistance() const {return m_distance;}
private:
    const ngl::Vec3 m_normal;
    const float m_distance;
};


#endif // PLANE_H*/
