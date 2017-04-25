/*#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include <glm/glm.hpp>
#include "collider.h"


class PhysicsObject
{
public:
    PhysicsObject(Collider* collider, const glm::vec3& velocity) :
                m_position(collider->getCentre()),
                m_oldPosition(collider->getCentre()),
                m_velocity(velocity),
                m_collider(collider){}
    PhysicsObject(const PhysicsObject& other);
    PhysicsObject operator=(PhysicsObject other);
    virtual ~PhysicsObject();

    void integrate(float delta);

    const glm::vec3& getPosition() const {return m_position;}
    const glm::vec3& getVelocity() const {return m_velocity;}
   // float getRadius() const {return m_radius;}


    const Collider& getCollider()
    {
        glm::vec3 translation = m_position - m_oldPosition;
        m_oldPosition = m_position;
        m_collider->transform(translation);

        return *m_collider;
    }

    void setVelocity(const glm::vec3& velocity) {m_velocity = velocity;}


   // mutable BoundingSphere m_boundingSphere;
private:
    glm::vec3 m_position;
    glm::vec3 m_oldPosition;
    glm::vec3 m_velocity;
  //  float m_radius;

    Collider* m_collider;

};


#endif // PHYSICSOBJECT_H*/
