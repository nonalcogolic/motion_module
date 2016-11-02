#pragma once


#include <QtWidgets/QWidget>

#include <qgl.h>


class COpenGLGraphicalWidget : public QGLWidget
{
   Q_OBJECT
public:
   COpenGLGraphicalWidget(QWidget *parent = 0);
   virtual ~COpenGLGraphicalWidget();

  void initializeGL();
  void resizeGL(int nWidth, int nHeight);
  void paintGL();


  void printAxises();

};

