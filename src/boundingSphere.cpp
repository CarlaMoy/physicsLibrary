#include "boundingSphere.h"

IntersectData BoundingSphere::intersectBoundingSphere(const BoundingSphere& other) const
{
  float radiusDistance = m_radius + other.getRadius();
  ngl::Vec3 direction = (other.getCentre() - m_centre);
  float centreDistance = direction.length();
  direction /= centreDistance; // normalise direction


  float distance = centreDistance - radiusDistance;

  return IntersectData(distance < 0, direction * distance);
}

/*IntersectData BoundingSphere::intersectPlane(const StaticPlane& static_collider) const
{

}*/

void BoundingSphere::transform(const ngl::Vec3& _translation)
{
  m_centre += _translation;
}
