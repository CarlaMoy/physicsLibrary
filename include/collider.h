#ifndef COLLIDER_H
#define COLLIDER_H

#include <glm/glm.hpp>
#include "intersectdata.h"
#include <ngl/NGLInit.h>

///@file collider.h
///@brief Class Collider. Has to be overwritten by a child class, corresponding to a collider type for implementation.
///@author Carla Moy
///@class Collider
class Collider
{
public:
    enum{
        TYPE_SPHERE,
        TYPE_AABB,
        TYPE_PLANE


      //  TYPE_SIZE
    };

    Collider(int type) : m_type(type){}
    ~Collider(){}

    IntersectData intersect(const Collider& other) const;
   // virtual IntersectData intersectGroundPlane();

    virtual void transform(const ngl::Vec3& translation) = 0;
    virtual ngl::Vec3 getCentre() const = 0;
    virtual ngl::Vec3 getSize() const = 0;
    virtual void drawObject() = 0;
    int getType() const {return m_type;}

private:
    int m_type;
};

#endif // COLLIDER_H
