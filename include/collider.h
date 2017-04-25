#ifndef COLLIDER_H
#define COLLIDER_H

#include <glm/glm.hpp>
#include "intersectdata.h"
#include <ngl/NGLInit.h>

class Collider
{
public:
    enum{
        TYPE_SPHERE,
        TYPE_AABB

      //  TYPE_SIZE
    };

    Collider(int type) : m_type(type){}

    IntersectData intersect(const Collider& other) const;

    virtual void transform(const ngl::Vec3& translation){}
    virtual ngl::Vec3 getCentre() const {return ngl::Vec3(0.0,0.0,0.0);}

    int getType() const {return m_type;}

private:
    int m_type;
};

#endif // COLLIDER_H
