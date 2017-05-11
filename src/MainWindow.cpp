#include "include/MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  m_gl = new NGLScene(this);
  ui->m_mainWindowGridLayout->addWidget(m_gl, 0, 0, 1, 1);
}

MainWindow::~MainWindow()
{
  delete ui;
}
