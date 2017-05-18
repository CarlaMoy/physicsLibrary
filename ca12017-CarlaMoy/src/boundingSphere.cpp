#include "boundingSphere.h"

IntersectData BoundingSphere::sphereIntersectBoundingSphere(const BoundingSphere& other) const
{
  float halfWidth = m_radius / 2;
  float halfWidth2 = other.getRadius() / 2;

  float radiusDistance = halfWidth  + halfWidth2;
  ngl::Vec3 direction = (other.getCentre() - m_centre);
  float centreDistance = direction.length();
  direction /= centreDistance; // normalise direction

  float distance = centreDistance - radiusDistance;

  return IntersectData(distance < 0, direction * distance);
}



IntersectData BoundingSphere::sphereIntersectAABB(const AABB& other) const
{
  //http://stackoverflow.com/questions/4578967/cube-sphere-intersection-test
  float halfWidth = m_radius / 2;
  float r2 = halfWidth * halfWidth;
  float dmin = 0;

  if(m_centre.m_x + halfWidth < other.getMinPoint().m_x)
    dmin += sqrt(m_centre.m_x + halfWidth - other.getMinPoint().m_x);
  else if(m_centre.m_x - halfWidth > other.getMaxPoint().m_x)
    dmin += sqrt(m_centre.m_x - halfWidth - other.getMaxPoint().m_x);

  if(m_centre.m_y + halfWidth < other.getMinPoint().m_y)
    dmin += sqrt(m_centre.m_y + halfWidth - other.getMinPoint().m_y);
  else if(m_centre.m_y - halfWidth > other.getMaxPoint().m_y)
    dmin += sqrt(m_centre.m_y - halfWidth - other.getMaxPoint().m_y);

  if(m_centre.m_z + halfWidth < other.getMinPoint().m_z)
    dmin += sqrt(m_centre.m_z + halfWidth - other.getMinPoint().m_z);
  else if(m_centre.m_z - halfWidth > other.getMaxPoint().m_z)
    dmin += sqrt(m_centre.m_z - halfWidth - other.getMaxPoint().m_z);

  //No proper check for direction of collision yet
  return IntersectData(dmin <= r2, ngl::Vec3(0.0,1.0,0.0));
}



void BoundingSphere::transform(const ngl::Vec3& _translation)
{
  m_centre += _translation;
}



void BoundingSphere::drawObject()
{
  ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
  prim->draw("sphere");
}



//IntersectData BoundingSphere::intersectGroundPlane()
//{
//  float groundYpos = 0.0;
//  ngl::Vec3 groundNormal = ngl::Vec3(0.0,1.0,0.0);

//  return IntersectData(groundYpos > m_centre.m_y - m_radius, groundNormal);
//}
