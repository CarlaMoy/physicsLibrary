#ifndef PLANE_H
#define PLANE_H

#include <glm/glm.hpp>
#include "boundingSphere.h"

class Plane
{
public:
    Plane(const ngl::Vec3& normal, float distance) : m_normal(normal), m_distance(distance){}

    Plane normalised() const;

    IntersectData intersectSphere(const BoundingSphere& other) const;

    const ngl::Vec3& getNormal() const {return m_normal;}
    float getDistance() const {return m_distance;}
private:
    const ngl::Vec3 m_normal;
    const float m_distance;
};


#endif // PLANE_H
