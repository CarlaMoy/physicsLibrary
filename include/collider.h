#ifndef COLLIDER_H
#define COLLIDER_H

#include <glm/glm.hpp>
#include "intersectdata.h"

class Collider
{
public:
    enum{
        TYPE_SPHERE,
        TYPE_AABB,

        TYPE_SIZE
    };

    Collider(int type) : m_type(type){}

    IntersectData intersect(const Collider& other) const;

    virtual void transform(const glm::vec3& translation){}
    virtual glm::vec3 getCentre() const {return glm::vec3(0.0,0.0,0.0);}

    int getType() const {return m_type;}

private:
    int m_type;
};

#endif // COLLIDER_H
