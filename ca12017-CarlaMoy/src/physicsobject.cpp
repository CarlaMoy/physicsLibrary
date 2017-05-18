/*#include "physicsobject.h"
#include "boundingSphere.h"
#include <iostream>
#include <cassert>
#include <cstring>

PhysicsObject::PhysicsObject(const PhysicsObject& other) :
    m_position(other.m_position),
    m_oldPosition(other.m_oldPosition),
    m_velocity(other.m_velocity),
    m_collider(other.m_collider)
{
    //m_collider->AddReference();
}

PhysicsObject PhysicsObject::operator=(PhysicsObject other)
{
    //Implemented using the copy/swap idiom.
    char* temp[sizeof(PhysicsObject)/sizeof(char)];
    memcpy(temp, this, sizeof(PhysicsObject));
    memcpy(this, &other, sizeof(PhysicsObject));
    memcpy(&other, temp, sizeof(PhysicsObject));
}
PhysicsObject::~PhysicsObject(){}


void PhysicsObject::integrate(float delta)
{
    m_position += m_velocity * delta;
}
*/
