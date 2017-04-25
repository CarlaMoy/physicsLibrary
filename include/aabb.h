#ifndef AABB_H
#define AABB_H

#include "intersectdata.h"
#include <glm/glm.hpp>
#include <ngl/NGLInit.h>

class AABB
{
public:
    AABB(const ngl::Vec3& minPoint, const ngl::Vec3& maxPoint): m_minPoint(minPoint), m_maxPoint(maxPoint){}
    //
    IntersectData IntersectAABB(const AABB& other) const;
    const ngl::Vec3& getMinPoint() const {return m_minPoint;}
    const ngl::Vec3& getMaxPoint() const {return m_maxPoint;}

private:
    const ngl::Vec3 m_minPoint;
    const ngl::Vec3 m_maxPoint;

};

#endif // AABB_H
