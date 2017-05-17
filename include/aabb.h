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
    ///@param
    AABB(ngl::Vec3 _position, const float& _width, const float& _height, const float& _depth): Collider(Collider::TYPE_AABB),
                                                                                               m_width(_width),
                                                                                               m_height(_height),
                                                                                               m_depth(_depth),
                                                                                               m_minPoint(minBound()),
                                                                                               m_maxPoint(maxBound()),
                                                                                               m_centre(_position){}
    ~AABB(){}

    IntersectData AABBintersectAABB(const AABB& other) const;
    IntersectData AABBintersectBoundingSphere(const BoundingSphere& other) const;
    const ngl::Vec3& getMinPoint() const {return m_minPoint;}
    const ngl::Vec3& getMaxPoint() const {return m_maxPoint;}


    void transform(const ngl::Vec3& translation) override;
    ngl::Vec3 getCentre() const override {return m_centre;}
    ngl::Vec3 getSize() const override {return ngl::Vec3(m_width, m_height, m_depth);}

private:
    const float m_width, m_height, m_depth;
    ngl::Vec3 m_minPoint;
    ngl::Vec3 m_maxPoint;

    ngl::Vec3 m_centre;


    ngl::Vec3 minBound();
    ngl::Vec3 maxBound();
    void setMinPoint() {m_minPoint = minBound();}
    void setMaxPoint() {m_maxPoint = maxBound();}

    void drawObject() override;

};

#endif // AABB_H
