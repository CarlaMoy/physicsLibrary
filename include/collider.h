/*#ifndef COLLIDER_H
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

    ///@brief Virtual transform because centre of object variable is defined by children. It might be better to have m_centre defined
    /// publicly in parent class. Then getSize can access m_centre in child class as required.
    virtual void transform(const ngl::Vec3& _translation){}//{}
    ///@brief virtual getCe
    virtual ngl::Vec3 getCentre() const{return ngl::Vec3(0.0,0.0,0.0);} //Backup if undefined by child
    virtual ngl::Vec3 getSize() const{return ngl::Vec3(1.0,1.0,1.0);}

    int getType() const {return m_type;}

private:
    int m_type;
};

#endif // COLLIDER_H*/

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
        TYPE_AABB,
        TYPE_PLANE


      //  TYPE_SIZE
    };

    Collider(int type) : m_type(type){}

    IntersectData intersect(const Collider& other) const;
   // virtual IntersectData intersectGroundPlane();

    virtual void transform(const ngl::Vec3& translation){}
    virtual ngl::Vec3 getCentre() const {return ngl::Vec3(0.0,0.0,0.0);}
    virtual ngl::Vec3 getSize() const{return ngl::Vec3(1.0,1.0,1.0);}
    int getType() const {return m_type;}

private:
    int m_type;
};

#endif // COLLIDER_H
