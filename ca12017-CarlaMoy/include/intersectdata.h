#ifndef INTERSECTDATA_H
#define INTERSECTDATA_H

#include <glm/glm.hpp>
#include <ngl/NGLInit.h>

///@file intersectdata.h
///@brief Basic collision manifold class to return intersection data required for collision response
///@author Carla Moy
///@class IntersectData

class IntersectData
{
public:
    ///@brief Constructor for IntersectData
    ///@param doesIntersect Boolean for checking whether two objects are intersecting
    ///@param direction The direction the two objects have intersected
    IntersectData(const bool doesIntersect, const ngl::Vec3 direction): m_doesIntersect(doesIntersect), m_direction(direction){}

    ///@brief Destructor for IntersecData
    ~IntersectData(){}

    ///@brief Method to check whether object is intersecting
    bool GetDoesIntersect() const{ return m_doesIntersect;}

    ///@brief Returns the distance scalar (length of direction)
    float getDistance() const {return m_direction.length();}
    ///@brief Returns direction vector
    const ngl::Vec3& getDirection() const {return m_direction;}

private:
    ///@brief Boolean for intersection check
    const bool m_doesIntersect;
    ///@brief Direction vector
    const ngl::Vec3 m_direction;
};


#endif // INTERSECTDATA_H

