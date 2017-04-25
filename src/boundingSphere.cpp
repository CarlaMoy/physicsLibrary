#include "boundingSphere.h"

IntersectData BoundingSphere::intersectBoundingSphere(const BoundingSphere& other) const
{
    float radiusDistance = m_radius + other.getRadius();
    ngl::Vec3 direction = (other.getCentre() - m_centre);
    float centreDistance = direction.length();
    direction /= centreDistance;


    float distance = centreDistance - radiusDistance;

    return IntersectData(distance < 0, direction * distance);
}

void BoundingSphere::transform(const ngl::Vec3& translation)
{
    m_centre += translation;
}
