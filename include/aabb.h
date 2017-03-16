#ifndef AABB_H
#define AABB_H

#include "intersectdata.h"
#include <glm/glm.hpp>

class AABB
{
public:
    AABB(const glm::vec3& minPoint, const glm::vec3& maxPoint): m_minPoint(minPoint), m_maxPoint(maxPoint){}
    //
    IntersectData IntersectAABB(const AABB& other) const;
    const glm::vec3& getMinPoint() const {return m_minPoint;}
    const glm::vec3& getMaxPoint() const {return m_maxPoint;}

private:
    const glm::vec3 m_minPoint;
    const glm::vec3 m_maxPoint;

};

#endif // AABB_H
