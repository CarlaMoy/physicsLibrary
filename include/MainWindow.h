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
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void on_pushButton_clicked();

private:
  Ui::MainWindow *m_ui;
  NGLScene *m_gl;
};

#endif // MAINWINDOW_H
