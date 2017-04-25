#include "rigidBody.h"
#include "boundingSphere.h"
#include <iostream>
#include <cassert>
#include <cstring>

RigidBody::RigidBody(const RigidBody& other) :
    m_position(other.m_position),
    m_oldPosition(other.m_oldPosition),
    m_velocity(other.m_velocity),
    m_collider(other.m_collider)
{
    //m_collider->AddReference();
}

RigidBody RigidBody::operator=(RigidBody other)
{
    //Implemented using the copy/swap idiom.
    char* temp[sizeof(RigidBody)/sizeof(char)];
    memcpy(temp, this, sizeof(RigidBody));
    memcpy(this, &other, sizeof(RigidBody));
    memcpy(&other, temp, sizeof(RigidBody));
}
RigidBody::~RigidBody(){}


void RigidBody::integrate(float delta)
{
    m_position += m_velocity * delta;
}


const Collider& RigidBody::getCollider()
{
    ngl::Vec3 translation = m_position - m_oldPosition;
    m_oldPosition = m_position;
    m_collider->transform(translation);

    return *m_collider;
}
