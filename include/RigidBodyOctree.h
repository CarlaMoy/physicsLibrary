#ifndef RIGIDBODYOCTREE_H__
#define RIGIDBODYOCTREE_H__

#include "AbstractOctree.h"
#include "rigidBody.h"

class Rigidbody;

class RigidBodyOctree : public AbstractOctree <RigidBody,ngl::Vec3>
{
  public :
     RigidBodyOctree(int _height, BoundingBox _limit)
       :
       AbstractOctree <RigidBody,ngl::Vec3> ( _height,  _limit)
     {}

     virtual void  checkCollisionOnNode(TreeNode <RigidBody> *node);



};

#endif

