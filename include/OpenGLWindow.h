#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QOpenGLWindow> // window
//widget is a component of larger window system
#include <QKeyEvent>
#include <QtGui/QApplication>

class OpenGLWindow : public QOpenGLWindow
{
    Q_OBJECT//must be here
public:
    OpenGLWindow();
    ~OpenGLWindow();
    void paintGL() override;
    void initializeGL() override;
    void resizeGL(int _w, int _h) override;
    void keyPressEvent(QKeyEvent * _event) override;
    void timerEvent(QTimerEvent * _event) override;

private:
    int m_width = 1024;
    int m_height = 720;
    float m_rotY = 0.0f;
    void drawTriangle();

};

#endif
