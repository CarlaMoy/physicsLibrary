#include "boundingSphere.h"

IntersectData BoundingSphere::sphereIntersectBoundingSphere(const BoundingSphere& other) const
{
  float radiusDistance = m_radius + other.getRadius();
  ngl::Vec3 direction = (other.getCentre() - m_centre);
  float centreDistance = direction.length();
  direction /= centreDistance; // normalise direction


  float distance = centreDistance - radiusDistance;

  return IntersectData(distance < 0, direction * distance);
}

IntersectData BoundingSphere::sphereIntersectAABB(const AABB& other) const
{
  //http://stackoverflow.com/questions/4578967/cube-sphere-intersection-test
  float r2 = m_radius * m_radius;
  float dmin = 0;


/*  for(int i=0; i<3; ++i)
  {
    if(m_centre[i] < other.getMinPoint()[i])
      dmin += sqrt(m_centre[i] - other.getMinPoint()[i]);
    else if(m_centre[i] > other.getMaxPoint()[i])
      dmin += sqrt(m_centre[i] - other.getMaxPoint()[i]);
  }*/

  if(m_centre.m_x + m_radius < other.getMinPoint().m_x)
    dmin += sqrt(m_centre.m_x + m_radius - other.getMinPoint().m_x);
  else if(m_centre.m_x - m_radius > other.getMaxPoint().m_x)
    dmin += sqrt(m_centre.m_x - m_radius - other.getMaxPoint().m_x);

  if(m_centre.m_y + m_radius < other.getMinPoint().m_y)
    dmin += sqrt(m_centre.m_y + m_radius - other.getMinPoint().m_y);
  else if(m_centre.m_y - m_radius > other.getMaxPoint().m_y)
    dmin += sqrt(m_centre.m_y - m_radius - other.getMaxPoint().m_y);

  if(m_centre.m_z + m_radius < other.getMinPoint().m_z)
    dmin += sqrt(m_centre.m_z + m_radius - other.getMinPoint().m_z);
  else if(m_centre.m_z - m_radius > other.getMaxPoint().m_z)
    dmin += sqrt(m_centre.m_z - m_radius - other.getMaxPoint().m_z);

  //https://learnopengl.com/#!In-Practice/2D-Game/Collisions/Collision-resolution
 /* glm::vec2 compass[] = {
    ngl::Vec3(0.0f, 1.0f, 0.0f),	// up
    ngl::Vec3(0.0f, -1.0f, 0.0f),	// down
    ngl::Vec3(1.0f, 0.0f, 0.0f),	// right
    ngl::Vec3(-1.0f, 0.0f, 0.0f),	// left
    ngl::Vec3(0.0f, 0.0f, 1.0f),	// front
    ngl::Vec3(0.0f, 0.0f, -1.0f)	// back
  };
  GLfloat max = 0.0f;
  GLuint best_match = -1;
  for (GLuint i = 0; i < 6; i++)
  {
    GLfloat dot_product = glm::dot(glm::normalize(target), compass[i]);
    if (dot_product > max)
    {
      max = dot_product;
      best_match = i;
    }
  }*/

  return IntersectData(dmin <= r2, ngl::Vec3(0.0,1.0,0.0));
}

/*IntersectData BoundingSphere::intersectPlane(const StaticPlane& static_collider) const
{

}*/

void BoundingSphere::transform(const ngl::Vec3& _translation)
{
  m_centre += _translation;
}

IntersectData BoundingSphere::intersectGroundPlane()
{
  float groundYpos = 0.0;
  ngl::Vec3 groundNormal = ngl::Vec3(0.0,1.0,0.0);


  return IntersectData(groundYpos > m_centre.m_y - m_radius, groundNormal);
}
