#include "physicsengine.h"
#include "boundingSphere.h"
#include <iostream>
#include <ngl/NGLInit.h>
#include <ngl/Random.h>
#include <ngl/VAOFactory.h>
#include <ngl/SimpleVAO.h>
#include <ngl/Util.h>


void PhysicsEngine::addObject(const RigidBody& object)
{
    m_rigidObjects.push_back(object);
}

void PhysicsEngine::simulate(float delta)
{
    for(unsigned int i = 0; i < m_rigidObjects.size(); i++)
    {
        m_rigidObjects[i].integrate(delta);

    }
}

void PhysicsEngine::handleCollisions()
{
    for(unsigned int i = 0; i < m_rigidObjects.size(); i++)
    {
        for(unsigned int j = i + 1; j < m_rigidObjects.size(); j++)
        {
            IntersectData intersectData = m_rigidObjects[i].getCollider().intersect(m_rigidObjects[j].getCollider());

            if(intersectData.GetDoesIntersect())
            {
                ngl::Vec3 direction = intersectData.getDirection();
                direction.normalize();
                m_rigidObjects[i].setVelocity(ngl::Vec3(m_rigidObjects[i].getVelocity().reflect(direction)));
                m_rigidObjects[j].setVelocity(ngl::Vec3(m_rigidObjects[j].getVelocity().reflect(direction)));
            }
        }
    }
}


void PhysicsEngine::updatePhysics()
{
    std::cout<<"updating\n";
}

void PhysicsEngine::drawPhysics()
{
    std::cout<<"drawing\n";
    m_vao->bind();

    struct Rigid
    {
        ngl::Vec3 pos;
        ngl::Vec3 colour;
    };

    std::vector<Rigid> rigid(m_rigidObjects.size());
    for(size_t i = 0; i < m_rigidObjects.size(); ++i)
    {
        rigid[i].pos = m_rigidObjects[i].getPosition();
        rigid[i].colour = m_rigidObjects[i].getColour();
    }

    m_vao->setData(ngl::SimpleVAO::VertexData(rigid.size()*sizeof(rigid),
                                              rigid[0].pos.m_x));
    m_vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(rigid), 0);
    m_vao->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(rigid),3);
    m_vao->setNumIndices(rigid.size());
    m_vao->draw();
    m_vao->unbind();
}

void PhysicsEngine::resetRigidBody(RigidBody &io_r)
{

}

void PhysicsEngine::loadRigidBodyVAO()
{

}
