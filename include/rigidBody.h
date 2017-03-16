#ifndef RIGID_BODY_H
#define RIGID_BODY_H

#include <iostream>
#include <stdlib.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>




class RigidBody
{
public:
    ///Constructor
    RigidBody();

private:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 AngularVelocity;
    glm::vec3 orientation;
    double mass;
    double size;
    double damping;


};



#endif
