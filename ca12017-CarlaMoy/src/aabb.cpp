#include "aabb.h"
#include <ngl/NGLStream.h>
#include <iostream>


IntersectData AABB::AABBintersectAABB(const AABB& other) const
{
  //Modified from : https://github.com/BennyQBD/3DEngineCpp/blob/7e0022e0d0e253f50ee14a00abcf095fa8fa667f/src/physics/aabb.cpp
  ngl::Vec3 dist1 = other.getMinPoint() - m_maxPoint;
  ngl::Vec3 dist2 = m_minPoint - other.getMaxPoint();
  float dist1Val = dist1.m_x + dist1.m_y + dist1.m_z;
  float dist2Val = dist2.m_x + dist2.m_y + dist2.m_z;
  ngl::Vec3 distances = (dist1Val > dist2Val)? dist1 : dist2;

  float maxDist = distances.m_x;

  if(distances.m_x > maxDist)
    maxDist = distances.m_x;
  else if(distances.m_y > maxDist)
    maxDist = distances.m_y;
  else if(distances.m_z > maxDist)
    maxDist = distances.m_z;

  return IntersectData(maxDist < 0, distances);
}



IntersectData AABB::AABBintersectBoundingSphere(const BoundingSphere& other) const
{
  //Modified from : http://stackoverflow.com/questions/4578967/cube-sphere-intersection-test
  float halfWidth = other.getRadius() / 2;
  float r2 = halfWidth * halfWidth;
  float dmin = 0;


  if(other.getCentre().m_x + halfWidth < m_minPoint.m_x)
    dmin += sqrt(other.getCentre().m_x + halfWidth - m_minPoint.m_x);
  else if(other.getCentre().m_x - halfWidth > m_maxPoint.m_x)
    dmin += sqrt(other.getCentre().m_x - halfWidth - m_maxPoint.m_x);

  if(other.getCentre().m_y + halfWidth < m_minPoint.m_y)
    dmin += sqrt(other.getCentre().m_y + halfWidth - m_minPoint.m_y);
  else if(other.getCentre().m_y - halfWidth > m_maxPoint.m_y)
    dmin += sqrt(other.getCentre().m_y - halfWidth - m_maxPoint.m_y);

  if(other.getCentre().m_z + halfWidth < m_minPoint.m_z)
    dmin += sqrt(other.getCentre().m_z + halfWidth - m_minPoint.m_z);
  else if(other.getCentre().m_z - halfWidth > m_maxPoint.m_z)
    dmin += sqrt(other.getCentre().m_z - halfWidth - m_maxPoint.m_z);

  //No proper check for direction of collision yet
  return IntersectData(dmin <= r2, ngl::Vec3(0.0,1.0,0.0));
}



void AABB::transform(const ngl::Vec3& _translation)
{
  m_centre += _translation;
  //update the min and max bound when centre in translated
  minBound();
  maxBound();
}



void AABB::minBound()
{
  float min_x = (m_centre.m_x - m_width/2);
  float min_y = (m_centre.m_y - m_height/2);
  float min_z = (m_centre.m_z - m_depth/2);

  m_minPoint = ngl::Vec3(min_x, min_y, min_z);
}



void AABB::maxBound()
{
  float max_x = (m_centre.m_x + m_width/2);
  float max_y = (m_centre.m_y + m_height/2);
  float max_z = (m_centre.m_z + m_depth/2);

  m_maxPoint = ngl::Vec3(max_x, max_y, max_z);
}



void AABB::drawObject()
{
  ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
  prim->draw("cube");
}
