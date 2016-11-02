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


  void mousePressEvent(QMouseEvent* pe);   // ������� �� ������� ����
  void mouseMoveEvent(QMouseEvent* pe);    // ����������� ����
  void mouseReleaseEvent(QMouseEvent* pe); // ������� ������� ����
  void wheelEvent(QWheelEvent *);          // �������� ��������

private:

  int xRotation, yRotation, zRotation, scale; // ���������� �������� � ��������
  QPoint mousePos; // ���������� ��� ����������� ������� ������� �����

};

