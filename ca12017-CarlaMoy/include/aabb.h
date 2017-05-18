#ifndef AABB_H
#define AABB_H

#include "intersectdata.h"
#include "boundingSphere.h"
#include <glm/glm.hpp>
#include <ngl/NGLInit.h>
#include "collider.h"

///@file aabb.h
///@brief AABB Class, child class of Collider for generating and checking AABB based collision.
///@author Carla Moy
///@class AABB

class BoundingSphere;

class AABB : public Collider
{
public:
    ///@brief Constructor for AABB
    ///@param _position Initial position
    ///@param _width Width of AABB
    ///@param _height Height of AABB
    ///@param _depth Depth of AABB
    AABB(ngl::Vec3 _position, const float& _width, const float& _height, const float& _depth): Collider(Collider::TYPE_AABB),
                                                                                               m_width(_width),
                                                                                               m_height(_height),
                                                                                               m_depth(_depth),
                                                                                               m_centre(_position){}
    ///@brief Destructor for AABB
    ~AABB(){}

    ///@brief Collision check for AABB-AABB
    ///@param other Other AABB to compare to
    IntersectData AABBintersectAABB(const AABB& other) const;
    ///@brief Collision check for AABB-Sphere
    ///@param other The sphere to compare to
    IntersectData AABBintersectBoundingSphere(const BoundingSphere& other) const;
    ///@brief Get minimum point of the AABB
    const ngl::Vec3& getMinPoint() const {return m_minPoint;}
    ///@brief Get maximum point of the AABB
    const ngl::Vec3& getMaxPoint() const {return m_maxPoint;}

    ///@brief Translates collider to new position and updates the min and max points,
    ///used in RigidBody.cpp for updating position for collision checks.
    ///@param translation The amount to translate, given by change in position each frame.
    void transform(const ngl::Vec3& translation) override;
    ///@brief Gets the centre of the object
    ngl::Vec3 getCentre() const override {return m_centre;}
    ///@brief Gets the size of the object
    ngl::Vec3 getSize() const override {return ngl::Vec3(m_width, m_height, m_depth);}

private:
    ///@brief Floats to inicate individual values for width height and depth of AABB
    const float m_width, m_height, m_depth;
    ///@brief Vectors for storing the min and max points of the AABB
    ngl::Vec3 m_minPoint;
    ngl::Vec3 m_maxPoint;

    ///@brief The vector to store the centre of the object
    ngl::Vec3 m_centre;

    ///@brief Methods to get the min and max points based on the size and centre of the AABB
    void minBound();
    void maxBound();

    ///@brief Method to draw cube for AABB
    void drawObject() override;

};

#endif // AABB_H
