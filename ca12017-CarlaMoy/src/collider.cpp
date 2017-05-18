#include "collider.h"
#include "boundingSphere.h"
#include <iostream>
#include <cstdlib>

//Modified from : https://github.com/BennyQBD/3DEngineCpp/blob/7e0022e0d0e253f50ee14a00abcf095fa8fa667f/src/physics/collider.cpp
IntersectData Collider::intersect(const Collider& other) const
{
  // Collision check for case: Sphere-Sphere
  if(m_type == TYPE_SPHERE && other.getType() == TYPE_SPHERE)
  {
    BoundingSphere* self = (BoundingSphere*)this;
    return self->sphereIntersectBoundingSphere((BoundingSphere&)other);
  }
  // Collision check for case: AABB-AABB
  if(m_type == TYPE_AABB && other.getType() == TYPE_AABB)
  {
    AABB* self = (AABB*)this;
    return self->AABBintersectAABB((AABB&)other);
  }
  // Collision check for case: Sphere-AABB
  if(m_type == TYPE_SPHERE && other.getType() == TYPE_AABB)
  {
    BoundingSphere* self = (BoundingSphere*)this;
    return self->sphereIntersectAABB((AABB&)other);
  }
  // Collision check for case: AABB-Sphere (could avoid code duplication with ordered container, but may be costly)
  if(m_type == TYPE_AABB && other.getType() == TYPE_SPHERE)
  {
    AABB* self = (AABB*)this;
    return self->AABBintersectBoundingSphere((BoundingSphere&)other);
  }


  std::cerr << "Error: Collisions not implemented between specified colliders.\n";
  exit(1);

  //Control should not reach this point
  return IntersectData(false, ngl::Vec3::zero());
}



