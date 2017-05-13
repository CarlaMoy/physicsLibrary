/*#ifndef AABB_H
#define AABB_H

#include "intersectdata.h"
#include <glm/glm.hpp>
#include <ngl/NGLInit.h>
#include "collider.h"

class AABB : public Collider
{
public:
    AABB(const float& _width, const float& _height, const float& _depth);
    IntersectData IntersectAABB(const AABB& other) const;
    const ngl::Vec3& getMinPoint() const {return m_minPoint;}
    const ngl::Vec3& getMaxPoint() const {return m_maxPoint;}
    virtual void transform(const ngl::Vec3& _translation);
    virtual ngl::Vec3 getCentre() const {return m_centre;}
    virtual ngl::Vec3 getSize() const {return ngl::Vec3(m_width, m_height, m_depth);}
    //const ngl::Vec3& getWidthHeightDepth() const {return ngl::Vec3(m_width, m_height, m_depth);}

private:

    const ngl::Vec3 m_minPoint;
    const ngl::Vec3 m_maxPoint;
    ngl::Vec3 m_centre;
    float m_width, m_height, m_depth;

    ngl::Vec3 minBound();
    ngl::Vec3 maxBound();

};

#endif // AABB_H*/

#ifndef AABB_H
#define AABB_H

#include "intersectdata.h"
#include "boundingSphere.h"
#include <glm/glm.hpp>
#include <ngl/NGLInit.h>
#include "collider.h"

class BoundingSphere;

class AABB : public Collider
{
public:
    //AABB(const ngl::Vec3& minPoint, const ngl::Vec3& maxPoint): m_minPoint(minPoint), m_maxPoint(maxPoint){}
    AABB(ngl::Vec3 _position, const float& _width, const float& _height, const float& _depth);
    ~AABB(){}

    IntersectData AABBintersectAABB(const AABB& other) const;
    IntersectData AABBintersectBoundingSphere(const BoundingSphere& other) const;
    const ngl::Vec3& getMinPoint() const {return m_minPoint;}
    const ngl::Vec3& getMaxPoint() const {return m_maxPoint;}

    void transform(const ngl::Vec3& translation) override;
    ngl::Vec3 getCentre() const override {return m_centre;}
    ngl::Vec3 getSize() const override {return ngl::Vec3(m_width, m_height, m_depth);}

private:
    float m_width, m_height, m_depth;
    const ngl::Vec3 m_minPoint;
    const ngl::Vec3 m_maxPoint;

    ngl::Vec3 m_centre;


    ngl::Vec3 minBound();
    ngl::Vec3 maxBound();

};

#endif // AABB_H
