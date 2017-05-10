#include <QMouseEvent>
#include <QGuiApplication>
#include <iostream>

#include "NGLScene.h"
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

//PhysicsEngine *world = NULL;

NGLScene::NGLScene()
{
  setTitle("Physics Engine");
  m_animate=true;
}


NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}



void NGLScene::resizeGL( int _w, int _h )
{
  m_cam.setShape( 45.0f, static_cast<float>( _w ) / _h, 0.05f, 350.0f );
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
}

void NGLScene::initializeGL()
{
  // we need to initialise the NGL lib which will load all of the OpenGL functions, this must
  // be done once we have a valid GL context but before we call any GL commands. If we dont do
  // this everything will crash
  ngl::NGLInit::instance();
  glClearColor(0.4f, 0.4f, 0.4f, 1.0f);			   // Grey Background
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

  // now we have associated this data we can link the shader
  // shader->linkProgramObject("Phong");
  // and make it active ready to load values
  //  (*shader)["Phong"]->use();
  shader->setShaderParam1i("Normalize",1);
//  shader->setShaderParam3f("Colour", 0.4,0.3,0.9);
  // the shader will use the currently active material and light0 so set them
  // ngl::Material m( ngl::STDMAT::BRONZE );
  // load our material values to the shader into the structure material (see Vertex shader)
  // m.loadToShader( "material" );

  // Now we will create a basic Camera from the graphics library
  // This is a static camera so it only needs to be set once
  // First create Values for the camera position
  ngl::Vec3 from(0.0f,2.0f,30.0f);
  ngl::Vec3 to(0.0f,0.0f,0.0f);
  ngl::Vec3 up(0,1,0);
  // now load to our new camera
  m_cam.set(from,to,up);
  // set the shape using FOV 45 Aspect Ratio based on Width and Height
  // The final two are near and far clipping planes of 0.5 and 10
  m_cam.setShape(45,720.0f/576.0f,0.05f,350);
  shader->setShaderParam3f("viewerPos",m_cam.getEye().m_x,m_cam.getEye().m_y,m_cam.getEye().m_z);

  m_lightAngle=0.0;
  m_light.reset( new ngl::Light(ngl::Vec3(0,2,2),ngl::Colour(1,1,1,1),ngl::Colour(1,1,1,1),ngl::LightModes::DIRECTIONALLIGHT));

  // now create our light this is done after the camera so we can pass the
  // transpose of the projection matrix to the light to do correct eye space
  // transformations
  ngl::Mat4 iv=m_cam.getViewMatrix();
  iv.transpose();
  m_light->setTransform(iv);
  // load these values to the shader as well
  m_light->loadToShader("light");


  ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
  prim->createSphere("sphere",1.0f,50);

  //  prim->createCylinder("cylinder",0.5f,1.4f,40,40);

  //  prim->createCone("cone",0.5,1.4f,20,20);

  // prim->createDisk("disk",0.8f,120);
  // prim->createTorus("torus",0.15f,0.4f,40,40);
  prim->createTrianglePlane("plane",200,200,200,200,ngl::Vec3(0,1,0));
  // as re-size is not explicitly called we need to do this.
  glViewport(0,0,width(),height());
  // this timer is going to trigger an event every 40ms which will be processed in the
  //
  m_physicsTimer =startTimer(1);
  // m_physicsTimer = startTimer(1);

  PhysicsEngine *world = PhysicsEngine::instance();

                                                //position            radius            velocity            colour            mass
  world->addObject(RigidBody(new BoundingSphere(ngl::Vec3(5.0,10.0,1.0), 1.0), ngl::Vec3(-1.0,0.0,0.0), ngl::Vec3(1.0,0.1,0.3), 1.0));
  world->addObject(RigidBody(new BoundingSphere(ngl::Vec3(-8.0,8.0,1.0), 6.0), ngl::Vec3(0.0,0.0,0.0), ngl::Vec3(0.4,0.1,0.7), 2.0));
//  world->addObject(RigidBody(new BoundingSphere(ngl::Vec3(0.0,5.0,3.0), 0.5), ngl::Vec3(0.0,0.0,0.0), ngl::Vec3(0.1,0.1,0.7), 2.0));
 // world->addObject(RigidBody(new BoundingSphere(ngl::Vec3(6.0,3.0,4.0), 1.0), ngl::Vec3(2.0,0.0,0.0), ngl::Vec3(0.1,0.1,0.7), 1.0));
//  world->addObject(RigidBody(new BoundingSphere(ngl::Vec3(-2.0,7.0,5.0), 1.0), ngl::Vec3(1.0,1.0,0.0), ngl::Vec3(0.1,0.1,0.7), 2.0));
//  world->addObject(RigidBody(new BoundingSphere(ngl::Vec3(-2.0,7.0,10.0), 1.0), ngl::Vec3(1.0,0.0,0.0), ngl::Vec3(0.1,0.1,0.7), 2.0));
  world->addObject(RigidBody(new BoundingSphere(ngl::Vec3(-2.0,7.0,-5.0), 2.0), ngl::Vec3(1.0,1.0,0.0), ngl::Vec3(0.1,0.6,0.7), 2.0));
//  world->addObject(RigidBody(new AABB(ngl::Vec3(5.0,10.0,2.0),1.0,3.0,1.0), ngl::Vec3(0.0,0.0,0.0), ngl::Vec3(0.1,0.5,1.0), 0.5));
//  world->addObject(RigidBody(new AABB(ngl::Vec3(0.0,10.0,0.0),1.0,1.0,1.0), ngl::Vec3(1.0,0.0,0.0), ngl::Vec3(0.1,0.5,1.0), 0.5));
//  ///@brief problem with AABB, also need to implement collision detection
// // world->addObject(RigidBody(new AABB()));
  world->getObject(0).setColour(ngl::Vec3(0.2,1.0,0.5));







}


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
  shader->setShaderParam3f("Colour",0.9, 0.7, 0.8);
}

void NGLScene::drawScene(const std::string &_shader)
{
  PhysicsEngine *world = PhysicsEngine::instance();
  // grab an instance of the shader manager
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  (*shader)[_shader]->use();
  // clear the screen and depth buffer
  // Rotation based on the mouse position for our global
  // transform
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

  // get the VBO instance and draw the built in teapot
  ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
  ngl::Random *rng=ngl::Random::instance();

  world->drawPhysics(m_mouseGlobalTX, &m_cam, _shader, world->getObject(0).getColour());
  std::cout<<world->getObject(0).getColour()<<"colour\n";
  std::cout<<world->getObject(0).getMass()<<"mass\n";


  m_transform.reset();
  {
    m_transform.setPosition(0.0,0.0,0.0);
    loadMatricesToShader();
    prim->draw("plane");
  } // and before a pop











}

void NGLScene::paintGL()
{


  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,m_win.width,m_win.height);
  drawScene("Phong");


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
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
    // turn on wirframe rendering
  case Qt::Key_W : glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); break;
    // turn off wire frame
  case Qt::Key_S : glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); break;
    // show full screen
  case Qt::Key_F : showFullScreen(); break;
    // show windowed
  case Qt::Key_N : showNormal(); break;
  case Qt::Key_Space : m_animate^=true; break;
  case Qt::Key_A : world->addObject(RigidBody(new AABB(ngl::Vec3(0.0,10.0,0.0),1.0,1.0,1.0), ngl::Vec3(1.0,0.0,0.0), ngl::Vec3(0.1,0.5,1.0), 0.5)); break;
  default : break;
  }
  // finally update the GLWindow and re-draw
  if (isExposed())
    update();
}

void NGLScene::updateLight()
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();

  (*shader)["Phong"]->use();
  // change the light angle
  m_lightAngle+=0.001;

  // now set this value and load to the shader
  m_light->setPosition(ngl::Vec3(4.0*cos(m_lightAngle),2,4.0*sin(m_lightAngle)));
  m_light->loadToShader("light");
}

void NGLScene::timerEvent(QTimerEvent *_event )
{
  PhysicsEngine *world = PhysicsEngine::instance();
  // if the timer is the light timer call the update light method
  if(_event->timerId() == m_physicsTimer  && m_animate==true)
  {
    updateLight();

    world->updatePhysics(0.005);
   // world->handleCollisions();
  }
  // re-draw GL
  update();
}


