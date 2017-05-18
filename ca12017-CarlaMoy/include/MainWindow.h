#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qfile.h>
#include <qtextstream.h>
#include <qmessagebox.h>
#include "NGLScene.h"

///@file MainWindow.h
///@brief Main Window class for QT UI.
///@author Carla Moy
///@class MainWindow
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  ///@brief MainWindow Constructor
  explicit MainWindow(QWidget *parent = 0);

  ///@brief MainWindow Destructor
  ~MainWindow();

public slots:
  ///@brief Method for creating rigid body by taking in the values from the UI
  /// to use for the UI button
  void createObject();

private:
  Ui::MainWindow *m_ui;
  NGLScene *m_gl;


};

#endif // MAINWINDOW_H
