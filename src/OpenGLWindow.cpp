#include "OpenGLWindow.h"
#include <GL/glu.h> //will not use in final



void OpenGLWindow::keyPressEvent(QKeyEvent * _event)
{
    switch(_event->key())
    {
        case Qt::Key_Escape : QApplication::exit(EXIT_SUCCESS); break;

        case Qt::Key_W : glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
        case Qt::Key_S : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
    }
    update();
}



OpenGLWindow::OpenGLWindow()
{
    setTitle("Qt5 and OpenGL");

}
OpenGLWindow::~OpenGLWindow()
{

}

void OpenGLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0,0,m_width,m_height);

    for(int i = 0; i <= 10; ++i)
    {
        drawTriangle();

    }



}

void OpenGLWindow::initializeGL()
{
    glClearColor(0.9,1,1,1);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0f, (float)m_width/m_height,0.01f, 10.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2,2,2,0,0,0,0,1,0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    startTimer(10);
}

void OpenGLWindow::resizeGL(int _w, int _h)
{
    m_width = _w;
    m_height = _h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)m_width/m_height,0.01f, 10.0f);
    glMatrixMode(GL_MODELVIEW);
}

void OpenGLWindow::timerEvent(QTimerEvent * _event)
{
    m_rotY += 0.5;

    update();
}

void OpenGLWindow::drawTriangle()
{
    glPushMatrix();
        glRotatef(m_rotY,0,1,0);
        glBegin(GL_TRIANGLES);
                glColor3f(1,0,0);
                glVertex3f(-1,-1,0);
                glColor3f(0,1,0);
                glVertex3f(1,-1,0);
                glColor3f(0,0,1);
                glVertex3f(0,1,0);
        glEnd();
    glPopMatrix();
}
