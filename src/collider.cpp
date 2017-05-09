#include "collider.h"
#include "boundingSphere.h"
#include <iostream>
#include <cstdlib>

IntersectData Collider::intersect(const Collider& other) const
{
  ///@brief Collision check for case: Sphere-Sphere
  if(m_type == TYPE_SPHERE && other.getType() == TYPE_SPHERE)
  {
    BoundingSphere* self = (BoundingSphere*)this;
    return self->intersectBoundingSphere((BoundingSphere&)other);
  }
  ///@brief Collision check for case: AABB-AABB
  if(m_type == TYPE_AABB && other.getType() == TYPE_AABB)
  {
    AABB* self = (AABB*)this;
    return self->intersectAABB((AABB&)other);
  }
  ///@brief Collision check for case: Sphere-AABB
  if(m_type == TYPE_SPHERE && other.getType() == TYPE_AABB)
  {
    BoundingSphere* self = (BoundingSphere*)this;
    return self->intersectAABB((AABB&)other);
  }

/*  if(m_type == TYPE_SPHERE && other.getType() == TYPE_PLANE)
  {
      BoundingSphere* self = (BoundingSphere*)this;
      return self->intersectGroundPlane();
  }*/


  std::cerr << "Error: Collisions not implemented between specified colliders.\n";
  exit(1);

  //Control should not reach this point
  return IntersectData(false, ngl::Vec3::zero());
}

/*void Collider::transform(const ngl::Vec3& _translation)
{
    m_centre += _translation;
}*/


