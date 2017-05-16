#include <boost/foreach.hpp>
#include "RigidBodyOctree.h"
#include "rigidBody.h"

void  RigidBodyOctree::checkCollisionOnNode(TreeNode <RigidBody> *node)
{
    if(node->m_height !=1)
    {
        for(int i=0;i<8;++i)
        {
            checkCollisionOnNode(node->m_child[i]);
        }
    }
    else
    {
        if(node->m_objectList.size()<=1)
        {
            return;
        }
        ngl::Vec3 P, Q, Vp, N, force;
        float Rp, Rq, dist, speed;
        BOOST_FOREACH(RigidBody *currentRigidBody,node->m_objectList)
        {
            P = currentRigidBody->getPosition();
            Vp = currentRigidBody->getVelocity();
            speed = Vp.length();
            Rp = currentRigidBody->transformCollider().getSize().m_x;
            force.m_x = force.m_y = force.m_z = 0.0;

            BOOST_FOREACH(RigidBody *testRigidBody,node->m_objectList )
            {
                // no need to self test
                if(testRigidBody==currentRigidBody)
                {
                  // continue
                  continue;
                }
                Q = testRigidBody->getPosition();
                Rq = testRigidBody->transformCollider().getSize().m_x;
                dist = Rq + Rq - (P-Q).length();
                if(dist > 0) // collision between P and Q
                {
                  N = P-Q;
                  N.normalize();
                  force += dist*N;
                }
            }
            Vp += force;
            Vp.normalize();
            currentRigidBody->setVelocity(Vp*speed);
        }
    }
}

