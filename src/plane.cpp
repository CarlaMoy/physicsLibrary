#include "plane.h"

Plane Plane::normalised() const
{
  float magnitude = m_normal.length();

  return Plane(m_normal/magnitude, m_distance/magnitude);

}

IntersectData Plane::intersectSphere(const BoundingSphere& other) const
{
  float distFromSphereCenter = (float)abs(m_normal.dot(other.getCentre()) + m_distance);
  float distFromSphere = distFromSphereCenter - other.getRadius();

  return IntersectData(distFromSphere < 0, m_normal * distFromSphere);
}

IntersectData Plane::intersectAABB(const AABB& other) const
{

}
