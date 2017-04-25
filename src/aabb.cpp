#include "aabb.h"


IntersectData AABB::IntersectAABB(const AABB& other) const
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
