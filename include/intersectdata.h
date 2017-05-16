#ifndef INTERSECTDATA_H
#define INTERSECTDATA_H

#include <glm/glm.hpp>
#include <ngl/NGLInit.h>

///@file intersectdata.h
///@brief Basic manifold geometry class to return intersection data required for collision response
///@author Carla Moy
///@class IntersectData

class IntersectData
{
public:
    //Constructor for intersect data
    IntersectData(const bool doesIntersect, const ngl::Vec3 direction): m_doesIntersect(doesIntersect), m_direction(direction){}
    ~IntersectData(){}
    //Check whether object is intersecting function
    bool GetDoesIntersect() const{ return m_doesIntersect;}
    //Returns distance scalar
    float getDistance() const {return m_direction.length();}
    //Returns direction vector
    const ngl::Vec3& getDirection() const {return m_direction;}

private:
    //Intersection check boolean
    const bool m_doesIntersect;
    //Direction vector
    const ngl::Vec3 m_direction;
};


#endif // INTERSECTDATA_H

