#include <iostream>
#include <stdlib.h>
#include <SDL.h>
#include <string>

#include "boundingSphere.h"
#include "aabb.h"
#include "plane.h"
#include "physicsobject.h"


#include <QtGui/QGuiApplication>
#include "OpenGLWindow.h"

#if defined(__linux__) || defined(WIN32)
    #include <GL/gl.h>
    #include<GL/glu.h>
#endif

#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#endif



/*int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    OpenGLWindow window;
    window.resize(1024,720);
    window.show();


    return app.exec();

}

*/

int main()
{

    Plane p1(glm::vec3(0.0,1.0,0.0), 0.0);

    BoundingSphere s1(glm::vec3(0.0,0.0,0.0), 1.0f);
    BoundingSphere s2(glm::vec3(0.0,1.0,0.0), 1.0f);
    BoundingSphere s3(glm::vec3(0.0,0.0,3.0), 1.0f);
    BoundingSphere s4(glm::vec3(1.0,5.0,0.0), 1.0f);

    IntersectData si1 = s1.intersectBoundingSphere(s2);
    IntersectData si2 = s1.intersectBoundingSphere(s3);
    IntersectData si3 = s1.intersectBoundingSphere(s4);

    std::cout<<"s1 intersect s2 :"<<si1.GetDoesIntersect()<<" distance: "<<si1.getDistance()<<"\n";
    std::cout<<"s1 intersect s3 :"<<si2.GetDoesIntersect()<<" distance: "<<si2.getDistance()<<"\n";
    std::cout<<"s1 intersect s4 :"<<si3.GetDoesIntersect()<<" distance: "<<si3.getDistance()<<"\n";


    AABB a(glm::vec3(0.0,0.0,0.0), glm::vec3(1.0,1.0,1.0));
    AABB b(glm::vec3(0.5,0.5,0.5), glm::vec3(2.0,2.0,2.0));
    AABB c(glm::vec3(3.0,3.0,3.0), glm::vec3(4.0,4.0,4.0));

    IntersectData a1 = a.IntersectAABB(b);
    IntersectData b1 = a.IntersectAABB(c);
    IntersectData c1 = b.IntersectAABB(c);

    std::cout << "intersects: " << a1.GetDoesIntersect() << "distance: " << a1.getDistance() << std::endl;
    std::cout << "intersects: " << b1.GetDoesIntersect() << "distance: " << b1.getDistance() << std::endl;
    std::cout << "intersects: " << c1.GetDoesIntersect() << "distance: " << c1.getDistance() << std::endl;

    IntersectData p1s1 = p1.intersectSphere(s1);
    IntersectData p1s2 = p1.intersectSphere(s2);
    IntersectData p1s3 = p1.intersectSphere(s3);
    IntersectData p1s4 = p1.intersectSphere(s4);



    std::cout << "plane intersects sphere: " << p1s1.GetDoesIntersect() << " distance: " << p1s1.getDistance() << std::endl;
    std::cout << "plane intersects sphere: " << p1s2.GetDoesIntersect() << " distance: " << p1s2.getDistance() << std::endl;
    std::cout << "plane intersects sphere: " << p1s3.GetDoesIntersect() << " distance: " << p1s3.getDistance() << std::endl;
    std::cout << "plane intersects sphere: " << p1s4.GetDoesIntersect() << " distance: " << p1s4.getDistance() << std::endl;




  //  PhysicsObject test(TYPE_SPHERE, 1.0);

//    test.integrate(20.0);

 //   glm::vec3 testPos = test.getPosition();
 //   glm::vec3 testVel = test.getVelocity();

 //   std::cout << testPos.x << " " << testPos.y << " " <<testPos.z << " Velocity " <<testVel.x << std::endl;

}


/*
void SDLErrorExit(const std::string &_msg);
void setupCamera();
void drawScene();

int main()
{
    std::cout<<"Hello World\n";

    if(SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
        SDLErrorExit("Unable to init SDL:");
    }

    SDL_Window *window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, 1024, 720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if(!window)
    {
        SDLErrorExit("Unable to create window");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_CreateContext(window);

    SDL_Event event;
    bool quit=false;

    glClearColor(0.25,0,0.3,1);
    setupCamera();

    while(!quit)
    {
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT : quit=true; break;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        drawScene();
        SDL_GL_SwapWindow(window);

    }

    return EXIT_SUCCESS;
}
void SDLErrorExit(const std::string &_msg)
{
    std::cerr<<_msg<<"\n";
    std::cerr<<SDL_GetError()<<"\n";
    exit(EXIT_FAILURE);
}
void setupCamera()
{
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0,1.0, 0.5f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(2,2,2,0,0,0,0,1,0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
}

void drawScene()
{
    static float rot = 0.f;
    glPushMatrix();
        glRotatef(++rot,0,1,0);
        glBegin(GL_TRIANGLES);
            glColor3f(1,0,0);
            glVertex3f(0,1,0);
            glColor3f(0,1,0);
            glVertex3f(1,-1,0);
            glColor3f(0,0,1);
            glVertex3f(-1,-1,0);
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glRotatef(++rot,2,0,0);
        glBegin(GL_TRIANGLES);
            glColor3f(1,0,0);
            glVertex3f(0,1,0);
            glColor3f(0,1,0);
            glVertex3f(1,-1,0);
            glColor3f(0,0,1);
            glVertex3f(-1,-3,0);
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glRotatef(++rot,0,0,1);
        glBegin(GL_TRIANGLES);
            glColor3f(1,0,0);
            glVertex3f(0,2,0);
            glColor3f(0,1,0);
            glVertex3f(1,-1,0);
            glColor3f(0,0,1);
            glVertex3f(-1,-1,0);
        glEnd();
    glPopMatrix();
}
*/
