#ifndef INTERSECTDATA_H
#define INTERSECTDATA_H

#include <glm/glm.hpp>

class IntersectData
{
public:
    //Constructor for intersect data
    IntersectData(const bool doesIntersect, const glm::vec3 direction): m_doesIntersect(doesIntersect), m_direction(direction){}
    //Check whether object is intersecting function
    bool GetDoesIntersect() const{ return m_doesIntersect;}
    //Returns distance scalar
    float getDistance() const {return glm::length(m_direction);}
    //Returns direction vector
    const glm::vec3& getDirection() const {return m_direction;}

private:
    //Intersection check boolean
    const bool m_doesIntersect;
    //Direction vector
    const glm::vec3 m_direction;
};


#endif // INTERSECTDATA_H
