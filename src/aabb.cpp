#include "aabb.h"
#include <ngl/NGLStream.h>
#include <iostream>


//AABB::AABB(ngl::Vec3 _position, const float& _width, const float& _height, const float& _depth): Collider(Collider::TYPE_AABB),
//  m_width(_width),
//  m_height(_height),
//  m_depth(_depth),
//  m_minPoint(minBound()),
//  m_maxPoint(maxBound()),
//  m_centre(_position)
//{
// // m_centre = (m_maxPoint - m_minPoint)/2.0;
//}


IntersectData AABB::AABBintersectAABB(const AABB& other) const
{
  //
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


//  if(m_maxPoint.m_x < other.getMinPoint().m_x || m_minPoint.m_x > other.getMaxPoint().m_x)
//  {
//    return IntersectData(true, ngl::Vec3::zero());
//  }
//  if(m_maxPoint.m_y < other.getMinPoint().m_y || m_minPoint.m_y > other.getMaxPoint().m_y)
//  {
//    return IntersectData(true, ngl::Vec3::zero());
//  }

//  return IntersectData(false, ngl::Vec3(1.0,1.0,1.0));



}

IntersectData AABB::AABBintersectBoundingSphere(const BoundingSphere& other) const
{
  //http://stackoverflow.com/questions/4578967/cube-sphere-intersection-test
  float r2 = other.getRadius() * other.getRadius();
  float dmin = 0;


  if(other.getCentre().m_x + other.getRadius() < m_minPoint.m_x)
    dmin += sqrt(other.getCentre().m_x + other.getRadius() - m_minPoint.m_x);
  else if(other.getCentre().m_x - other.getRadius() > m_maxPoint.m_x)
    dmin += sqrt(other.getCentre().m_x - other.getRadius() - m_maxPoint.m_x);

  if(other.getCentre().m_y + other.getRadius() < m_minPoint.m_y)
    dmin += sqrt(other.getCentre().m_y + other.getRadius() - m_minPoint.m_y);
  else if(other.getCentre().m_y - other.getRadius() > m_maxPoint.m_y)
    dmin += sqrt(other.getCentre().m_y - other.getRadius() - m_maxPoint.m_y);

  if(other.getCentre().m_z + other.getRadius() < m_minPoint.m_z)
    dmin += sqrt(other.getCentre().m_z + other.getRadius() - m_minPoint.m_z);
  else if(other.getCentre().m_z - other.getRadius() > m_maxPoint.m_z)
    dmin += sqrt(other.getCentre().m_z - other.getRadius() - m_maxPoint.m_z);


  return IntersectData(dmin <= r2, ngl::Vec3(0.0,1.0,0.0));
}


void AABB::transform(const ngl::Vec3& _translation)
{
  m_centre += _translation;
  setMinPoint();
  setMaxPoint();
  std::cout<<m_maxPoint<<"maxPoint..............\n";
  std::cout<<m_minPoint<<"minPoint..............\n";
  std::cout<<m_centre<<"centre.............\n";
}



ngl::Vec3 AABB::minBound()
{
  float min_x = (m_centre.m_x - m_width/2);
  float min_y = (m_centre.m_y - m_height/2);
  float min_z = (m_centre.m_z - m_depth/2);
   std::cout<<m_centre<<"centre2.............\n";
   std::cout<<m_width<<"width.............\n";

  return ngl::Vec3(min_x, min_y, min_z);
}

ngl::Vec3 AABB::maxBound()
{
  float max_x = (m_centre.m_x + m_width/2);
  float max_y = (m_centre.m_y + m_height/2);
  float max_z = (m_centre.m_z + m_depth/2);

  return ngl::Vec3(max_x, max_y, max_z);
}
