#include "include/MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  m_ui(new Ui::MainWindow)
{
  m_ui->setupUi(this);
  m_gl = new NGLScene(this);
  m_ui->m_mainWindowGridLayout->addWidget(m_gl, 0, 0, 1, 1);
  connect(m_ui->m_xPos, SIGNAL(valueChanged(double)), m_gl, SLOT(changeGravity(double)));

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
