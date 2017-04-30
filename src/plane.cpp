#include "plane.h"

StaticPlane StaticPlane::normalised() const
{
  float magnitude = m_normal.length();

  return StaticPlane(m_normal/magnitude, m_distance/magnitude);

}

IntersectData StaticPlane::intersectSphere(const BoundingSphere& other) const
{
  float distFromSphereCenter = 1.0f;//ngl::float::abs(m_normal.dot(other.getCentre()) + m_distance);
  float distFromSphere = distFromSphereCenter - other.getRadius();

  return IntersectData(distFromSphere < 0, m_normal * distFromSphere);
}
