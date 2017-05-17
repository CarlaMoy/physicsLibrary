#include "include/MainWindow.h"
#include "ui_MainWindow.h"
#include <ngl/NGLInit.h>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  m_ui(new Ui::MainWindow)
{
  m_ui->setupUi(this);
  m_gl = new NGLScene(this);
  m_ui->m_mainWindowGridLayout->addWidget(m_gl, 0, 0, 1, 1);
  connect(m_ui->m_gravity, SIGNAL(valueChanged(double)), m_gl, SLOT(changeGravity(double)));
  connect(m_ui->m_restitution, SIGNAL(valueChanged(double)), m_gl, SLOT(changeRestitution(double)));
  connect(m_ui->m_newRigidBody, SIGNAL(released()), this, SLOT(createObject()));
  connect(m_ui->m_bounds, SIGNAL(toggled(bool)), m_gl, SLOT(boundingAreaBool(bool)));

  this->setWindowTitle(QString("Physics Engine"));
}

MainWindow::~MainWindow()
{
  delete m_ui;
}

void MainWindow::on_pushButton_clicked() //taken from
{
  QFile file("C:\\Users\\");
  if(!file.open(QIODevice::ReadOnly))
    QMessageBox::information(0, "info", file.errorString());
  QTextStream in(&file);

 // m_ui->textEdit->


}

void MainWindow::createObject()
{
  const float xPos = static_cast<float>(m_ui->m_xPos->value());
  const float yPos = static_cast<float>(m_ui->m_yPos->value());
  const float zPos = static_cast<float>(m_ui->m_zPos->value());

  const float xVel = static_cast<float>(m_ui->m_xVel->value());
  const float yVel = static_cast<float>(m_ui->m_yVel->value());
  const float zVel = static_cast<float>(m_ui->m_zVel->value());

  const float rCol = static_cast<float>(m_ui->m_rCol->value());
  const float gCol = static_cast<float>(m_ui->m_gCol->value());
  const float bCol = static_cast<float>(m_ui->m_bCol->value());

  const float mass = static_cast<float>(m_ui->m_mass->value());
  const float size = static_cast<float>(m_ui->m_size->value());
  const float friction = static_cast<float>(m_ui->m_friction->value());

  const int colliderType = m_ui->m_collider->currentIndex();

  std::cout<<colliderType<<"------>type Number\n";

  ngl::Vec3 pos = ngl::Vec3(xPos, yPos, zPos);
  ngl::Vec3 vel = ngl::Vec3(xVel, yVel, zVel);
  ngl::Vec3 col = ngl::Vec3(rCol, gCol, bCol);

  m_gl->createRigidBody(colliderType, pos, vel, col, mass, size, friction);
}
