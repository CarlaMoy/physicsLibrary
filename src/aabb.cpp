#include "aabb.h"


AABB::AABB(ngl::Vec3 _position, const float& _width, const float& _height, const float& _depth): Collider(Collider::TYPE_AABB),
  m_width(_width),
  m_height(_height),
  m_depth(_depth),
  m_minPoint(minBound()),
  m_maxPoint(maxBound()),
  m_centre(_position)
{
 // m_centre = (m_maxPoint - m_minPoint)/2.0;
}


IntersectData AABB::intersectAABB(const AABB& other) const
{
  ngl::Vec3 dist1 = other.getMinPoint() - m_maxPoint;
  ngl::Vec3 dist2 = m_minPoint - other.getMaxPoint();
  float dist1Val = dist1.m_x + dist1.m_y + dist1.m_z;
  float dist2Val = dist2.m_x + dist2.m_y + dist2.m_z;
  ngl::Vec3 distances = (dist1Val > dist2Val)? dist1 : dist2;

  float maxDist = distances.m_x;

  //   for(float i=0; i<3; ++i)
  //       if(distances[i] > maxDist)
  //           maxDist = distances[i];
  if(distances.m_x > maxDist)
    maxDist = distances.m_x;
  else if(distances.m_y > maxDist)
    maxDist = distances.m_y;
  else if(distances.m_z > maxDist)
    maxDist = distances.m_z;

  return IntersectData(maxDist < 0, distances);


}
///@brief Could avoid duplicate code
void AABB::transform(const ngl::Vec3& _translation)
{
  m_centre += _translation;
}



ngl::Vec3 AABB::minBound()
{
  float min_x = m_centre.m_x - m_width/2;
  float min_y = m_centre.m_y - m_height/2;
  float min_z = m_centre.m_z - m_depth/2;

  return ngl::Vec3(min_x, min_y, min_z);
}

ngl::Vec3 AABB::maxBound()
{
  float max_x = m_centre.m_x + m_width/2;
  float max_y = m_centre.m_y + m_height/2;
  float max_z = m_centre.m_z + m_depth/2;

  return ngl::Vec3(max_x, max_y, max_z);
}
