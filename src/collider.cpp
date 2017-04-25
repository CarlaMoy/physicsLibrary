#include "collider.h"
#include "boundingSphere.h"
#include <iostream>
#include <cstdlib>

IntersectData Collider::intersect(const Collider& other) const
{
    if(m_type == TYPE_SPHERE && other.getType() == TYPE_SPHERE)
    {
        BoundingSphere* self = (BoundingSphere*)this;
        return self->intersectBoundingSphere((BoundingSphere&)other);
    }

    std::cerr << "Error: Collisions not implemented between specified colliders.\n";
    exit(1);

    //Control should not reach this point
    return IntersectData(false, ngl::Vec3::zero());
}

