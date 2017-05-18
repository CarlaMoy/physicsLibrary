#include "NGLScene.h"

#include <QMouseEvent>
#include <QGuiApplication>
#include <iostream>

#include <ngl/Camera.h>
#include <ngl/Light.h>
#include <ngl/Material.h>
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <ngl/Random.h>
#include <ngl/NGLStream.h>

#include "physicsengine.h"
#include "boundingSphere.h"
#include "aabb.h"
#include "ConfigFile.h"


NGLScene::NGLScene(QWidget *_parent) : QOpenGLWidget(_parent)
{
  m_animate=true;
  setFocusPolicy(Qt::StrongFocus);
}



NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}


//----------------------------------------------------------------------------------------------------------------------
//Start of code by Jon Macey

void NGLScene::resizeGL( int _w, int _h )
{
  m_cam.setShape( 45.0f, static_cast<float>( _w ) / _h, 0.05f, 350.0f );
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
}



void NGLScene::initializeGL()
{
  ngl::NGLInit::instance();
  glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // now to load the shader and set the values
  // grab an instance of shader manager
  ngl::ShaderLib* shader = ngl::ShaderLib::instance();
  // we are creating a shader called Phong to save typos
  // in the code create some constexpr
  constexpr auto shaderProgram = "Phong";
  constexpr auto vertexShader  = "PhongVertex";
  constexpr auto fragShader    = "PhongFragment";
  // create the shader program
  shader->createShaderProgram( shaderProgram );
  // now we are going to create empty shaders for Frag and Vert
  shader->attachShader( vertexShader, ngl::ShaderType::VERTEX );
  shader->attachShader( fragShader, ngl::ShaderType::FRAGMENT );
  // attach the source
  shader->loadShaderSource( vertexShader, "shaders/ColourVert.glsl" );
  shader->loadShaderSource( fragShader, "shaders/ColourFrag.glsl" );
  // compile the shaders
  shader->compileShader( vertexShader );
  shader->compileShader( fragShader );
  // add them to the program
  shader->attachShaderToProgram( shaderProgram, vertexShader );
  shader->attachShaderToProgram( shaderProgram, fragShader );


  // now we have associated that data we can link the shader
  shader->linkProgramObject( shaderProgram );
  // and make it active ready to load values
  ( *shader )[ shaderProgram ]->use();

  shader->setShaderParam1i("Normalize",1);

  ngl::Vec3 from(0.0f,0.01f,50.0f);
  ngl::Vec3 to(0.0f,0.0f,0.0f);
  ngl::Vec3 up(0,1,0);
  // now load to our new camera
  m_cam.set(from,to,up);

  m_cam.setShape(45,720.0f/576.0f,0.05f,350);
  shader->setShaderParam3f("viewerPos",m_cam.getEye().m_x,m_cam.getEye().m_y,m_cam.getEye().m_z);

  m_lightAngle=0.0;
  m_light.reset( new ngl::Light(ngl::Vec3(0,2,2),ngl::Colour(1,1,1,1),ngl::Colour(1,1,1,1),ngl::LightModes::DIRECTIONALLIGHT));

  ngl::Mat4 iv=m_cam.getViewMatrix();
  iv.transpose();
  m_light->setTransform(iv);
  // load these values to the shader as well
  m_light->loadToShader("light");


  ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
  prim->createSphere("sphere",0.5f,50);
;
  prim->createTrianglePlane("plane",200,200,200,200,ngl::Vec3(0,1,0));

  glViewport(0,0,width(),height());

//End of code by Jon Macey
//----------------------------------------------------------------------------------------------------------------------


  m_physicsTimer =startTimer(1);

  PhysicsEngine *world = PhysicsEngine::instance();

  changeGravity(0);

  configFileParser(); //creates a rigid body based on config file values

                                                //position            radius            velocity            colour            mass  friction coeff
  world->addObject(RigidBody(new AABB(ngl::Vec3(40.0,10.0,1.0), 5.0, 6.0, 2.0), ngl::Vec3(-1.0,0.0,0.0), ngl::Vec3(0.5,0.1,0.7), 5.0, 0.05));
  world->addObject(RigidBody(new AABB(ngl::Vec3(20.0,10.0,1.0), 5.0, 6.0, 2.0), ngl::Vec3(-1.0,0.0,0.0), ngl::Vec3(0.9,0.1,0.7), 2.0, 0.4));
  world->addObject(RigidBody(new BoundingSphere(ngl::Vec3(-15.0,10.0,1.0), 5.0), ngl::Vec3(0.7,0.0,0.0), ngl::Vec3(1.0,0.1,0.3), 0.5, 0.005));



}

//----------------------------------------------------------------------------------------------------------------------
//Start of modified code by Jon Macey

void NGLScene::loadMatricesToShader()
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();

  ngl::Mat4 MV;
  ngl::Mat4 MVP;
  ngl::Mat3 normalMatrix;
  ngl::Mat4 M;
  M=m_transform.getMatrix()*m_mouseGlobalTX;
  MV=  M*m_cam.getViewMatrix();
  MVP=  MV*m_cam.getProjectionMatrix();
  normalMatrix=MV;
  normalMatrix.inverse();
  shader->setShaderParamFromMat4("MV",MV);
  shader->setShaderParamFromMat4("MVP",MVP);
  shader->setShaderParamFromMat3("normalMatrix",normalMatrix);
  shader->setShaderParamFromMat4("M",M);
  shader->setShaderParam3f("Colour",0.7, 0.7, 0.8);
}



void NGLScene::drawScene(const std::string &_shader)
{
  // grab neccessary instances
  PhysicsEngine *world = PhysicsEngine::instance();

  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  (*shader)[_shader]->use();

  ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();


  ngl::Mat4 rotX;
  ngl::Mat4 rotY;
  // create the rotation matrices
  rotX.rotateX(m_win.spinXFace);
  rotY.rotateY(m_win.spinYFace);
  // multiply the rotations
  m_mouseGlobalTX=rotY*rotX;
  // add the translations
  m_mouseGlobalTX.m_m[3][0] = m_modelPos.m_x;
  m_mouseGlobalTX.m_m[3][1] = m_modelPos.m_y;
  m_mouseGlobalTX.m_m[3][2] = m_modelPos.m_z;

  world->drawPhysics(m_mouseGlobalTX, &m_cam, _shader);

  m_transform.reset();
  {
    m_transform.setPosition(0.0,0.0,0.0);
    loadMatricesToShader();
    prim->draw("plane");
  }
}



void NGLScene::paintGL()
{

  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,m_win.width,m_win.height);
  drawScene("Phong");
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

}


//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseMoveEvent( QMouseEvent* _event )
{
  // note the method buttons() is the button state when event was called
  // that is different from button() which is used to check which button was
  // pressed when the mousePress/Release event is generated
  if ( m_win.rotate && _event->buttons() == Qt::LeftButton )
  {
    int diffx = _event->x() - m_win.origX;
    int diffy = _event->y() - m_win.origY;
    m_win.spinXFace += static_cast<int>( 0.5f * diffy );
    m_win.spinYFace += static_cast<int>( 0.5f * diffx );
    m_win.origX = _event->x();
    m_win.origY = _event->y();
    update();
  }
  // right mouse translate code
  else if ( m_win.translate && _event->buttons() == Qt::RightButton )
  {
    int diffX      = static_cast<int>( _event->x() - m_win.origXPos );
    int diffY      = static_cast<int>( _event->y() - m_win.origYPos );
    m_win.origXPos = _event->x();
    m_win.origYPos = _event->y();
    m_modelPos.m_x += INCREMENT * diffX;
    m_modelPos.m_y -= INCREMENT * diffY;
    update();
  }
}


//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mousePressEvent( QMouseEvent* _event )
{
  // that method is called when the mouse button is pressed in this case we
  // store the value where the maouse was clicked (x,y) and set the Rotate flag to true
  if ( _event->button() == Qt::LeftButton )
  {
    m_win.origX  = _event->x();
    m_win.origY  = _event->y();
    m_win.rotate = true;
  }
  // right mouse translate mode
  else if ( _event->button() == Qt::RightButton )
  {
    m_win.origXPos  = _event->x();
    m_win.origYPos  = _event->y();
    m_win.translate = true;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseReleaseEvent( QMouseEvent* _event )
{
  // that event is called when the mouse button is released
  // we then set Rotate to false
  if ( _event->button() == Qt::LeftButton )
  {
    m_win.rotate = false;
  }
  // right mouse translate mode
  if ( _event->button() == Qt::RightButton )
  {
    m_win.translate = false;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::wheelEvent( QWheelEvent* _event )
{

  // check the diff of the wheel position (0 means no change)
  if ( _event->delta() > 0 )
  {
    m_modelPos.m_z += ZOOM;
  }
  else if ( _event->delta() < 0 )
  {
    m_modelPos.m_z -= ZOOM;
  }
  update();
}
//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  PhysicsEngine *world = PhysicsEngine::instance();
  ngl::Random *rng=ngl::Random::instance();
  // this method is called every time the main window recives a key event.
  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
  case Qt::Key_Space : m_animate^=true; break;
  case Qt::Key_A :world->addObject(RigidBody(new AABB(ngl::Vec3(rng->randomNumber(100),rng->randomPositiveNumber(50),rng->randomNumber(100)),
                                                      rng->randomPositiveNumber(5),rng->randomPositiveNumber(5),rng->randomPositiveNumber(5)),
                                                      rng->getRandomVec3(), rng->getRandomVec3(), rng->randomPositiveNumber(5),
                                                      rng->randomPositiveNumber(1))); break;
  case Qt::Key_B :world->addObject(RigidBody(new BoundingSphere(ngl::Vec3(rng->randomNumber(100),rng->randomPositiveNumber(50),rng->randomNumber(100)),
                                                                rng->randomPositiveNumber(5)),rng->getRandomVec3(), rng->getRandomVec3(),
                                                                rng->randomPositiveNumber(5), rng->randomPositiveNumber(1))); break;
  case Qt::Key_G : world->setGravity(9);
  case Qt::Key_R : resetPhysicsWorld(); break;

  case Qt::Key_1 : world->addWind(ngl::Vec3(0.0,5.0,0.0)); break;
  case Qt::Key_2 : world->addWind(ngl::Vec3(0.0,-5.0,0.0)); break;
  case Qt::Key_Up : world->addWind(ngl::Vec3(0.0,0.0,-5.0)); break;
  case Qt::Key_Down : world->addWind(ngl::Vec3(0.0,0.0,5.0)); break;
  case Qt::Key_Left : world->addWind(ngl::Vec3(-5.0,0.0,0.0)); break;
  case Qt::Key_Right : world->addWind(ngl::Vec3(5.0,0.0,0.0)); break;
  default : break;
  }
    update();
}
//----------------------------------------------------------------------------------------------------------------------

void NGLScene::timerEvent(QTimerEvent *_event )
{
  PhysicsEngine *world = PhysicsEngine::instance();
  // if the timer is the physics timer call the update phyiscs world method
  if(_event->timerId() == m_physicsTimer  && m_animate==true)
  {

    world->updatePhysics(0.1);
  }
  update();
}

//End of modified code from Jon Macey
//----------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------
                                //Methods for the UI
//----------------------------------------------------------------------------------------------------------------------

void NGLScene::changeGravity(double _value)
{
  PhysicsEngine *world = PhysicsEngine::instance();
  world->resetForces();
  world->setGravity(static_cast<float>(_value));
}
//----------------------------------------------------------------------------------------------------------------------

void NGLScene::resetPhysicsWorld()
{
  PhysicsEngine *world = PhysicsEngine::instance();
  world->resetWorld();
}
//----------------------------------------------------------------------------------------------------------------------

void NGLScene::changeRestitution(double _restitution)
{
  PhysicsEngine *world = PhysicsEngine::instance();
  world->setRestitutionCoeff(static_cast<float>(_restitution));
}
//----------------------------------------------------------------------------------------------------------------------

void NGLScene::createRigidBody(int _type, ngl::Vec3 _pos, ngl::Vec3 _vel, ngl::Vec3 _col, float _mass, float _size, float _friction)
{
  PhysicsEngine *world = PhysicsEngine::instance();
  switch(_type)
  {
    case 0 : world->addObject(RigidBody(new BoundingSphere(_pos, _size), _vel, _col, _mass, _friction)); break;
    case 1 : world->addObject(RigidBody(new AABB(_pos, _size, _size, _size), _vel, _col, _mass, _friction)); break;
  }
}
//----------------------------------------------------------------------------------------------------------------------

//Turn on or off the ground and wall collisions
void NGLScene::boundingAreaBool(bool _choice)
{
  PhysicsEngine *world = PhysicsEngine::instance();
  world->setBoundingArea(_choice);
}

//----------------------------------------------------------------------------------------------------------------------
                                //Passing initial values through .cfg file
//----------------------------------------------------------------------------------------------------------------------

void NGLScene::configFileParser()
{
  ConfigFile cfg("PhysicsLibraryValues.cfg");

  float xPos = cfg.getValueOfKey<float>("xPos", 1);
  float yPos = cfg.getValueOfKey<float>("yPos", 1);
  float zPos = cfg.getValueOfKey<float>("zPos", 1);

  float xVel = cfg.getValueOfKey<float>("xVel", 1);
  float yVel = cfg.getValueOfKey<float>("yVel", 1);
  float zVel = cfg.getValueOfKey<float>("zVel", 1);

  float rCol = cfg.getValueOfKey<float>("rCol", 1);
  float gCol = cfg.getValueOfKey<float>("gCol", 1);
  float bCol = cfg.getValueOfKey<float>("bCol", 1);

  float mass = cfg.getValueOfKey<float>("mass", 1);
  float size = cfg.getValueOfKey<float>("size", 1);
  int type = cfg.getValueOfKey<int>("type", 1);
  float friction = cfg.getValueOfKey<float>("friction", 1);

  ngl::Vec3 pos = ngl::Vec3(xPos, yPos, zPos);
  ngl::Vec3 vel = ngl::Vec3(xVel, yVel, zVel);
  ngl::Vec3 col = ngl::Vec3(rCol, bCol, gCol);

  createRigidBody(type, pos, vel, col, mass, size, friction);
}
