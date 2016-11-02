#pragma once


#include <QtWidgets/QWidget>

#include <qgl.h>
#include "qevent.h"


class COpenGLGraphicalWidget : public QGLWidget
{
   Q_OBJECT
public: 
   COpenGLGraphicalWidget(QWidget *parent = 0);
   virtual ~COpenGLGraphicalWidget();

  void initializeGL();
  void resizeGL(int nWidth, int nHeight);
  void paintGL();


  void drawAxises();
  void drawSensor();


  void mousePressEvent(QMouseEvent* pe);   // нажатие на клавишу мыши
  void mouseMoveEvent(QMouseEvent* pe);    // перемещение мыши
  void mouseReleaseEvent(QMouseEvent* pe); // отжатие клавиши мыши
  void wheelEvent(QWheelEvent *);          // вращение колесика

private:

  int xRotation, yRotation, zRotation, scale; // переменные поворота и масштаба
  QPoint mousePos; // переменная для запоминания позиции нажатия мышки

};

