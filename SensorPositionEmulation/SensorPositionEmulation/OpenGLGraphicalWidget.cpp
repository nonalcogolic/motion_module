#include "OpenGLGraphicalWidget.h"



COpenGLGraphicalWidget::COpenGLGraphicalWidget(QWidget *parent) // �����������
   : QGLWidget(parent)
{
   resizeGL(200, 200); // ������ ������� ����
   resize(200, 200);
}


COpenGLGraphicalWidget::~COpenGLGraphicalWidget()
{

}


void COpenGLGraphicalWidget::initializeGL()
{
   qglClearColor(Qt::white); // ��������� ����� ����� ������
   glEnable(GL_DEPTH_TEST); // ������ ������� �������� ��������
   glShadeModel(GL_FLAT); // ������� ����� ����������� ������
   glEnable(GL_CULL_FACE); // �������, ��� ����� ������� ������ ������� �����������
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // ������ ����� ��������� � ����� ������
}

void COpenGLGraphicalWidget::resizeGL(int nWidth, int nHeight)
{
   glViewport(0, 0, nHeight, nHeight); // ��������� ����� ������
   glMatrixMode(GL_PROJECTION); // ��������� ������ �������
   glLoadIdentity(); // �������� �������
   
}

void COpenGLGraphicalWidget::paintGL() // ���������
{

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������� ������
   glMatrixMode(GL_MODELVIEW); 
   glLoadIdentity();           // �������� ��������� �������

  
   glScalef(0.1, 0.1, 0.1);
  
   glRotatef(20, 1, 1, 0);
   printAxises();

 
}

void COpenGLGraphicalWidget::printAxises()
{
   QColor axisColor(0, 0, 0, 255);
   qglColor(axisColor);
   glBegin(GL_LINES);
   glVertex3f(0, -1, 0);
   glVertex3f(0, 1, 0);
   glEnd();

   glBegin(GL_LINES);
   glVertex3f(-1, 0, 0);
   glVertex3f(1, 0, 0);
   glEnd();

   glBegin(GL_LINES);
   glVertex3f(0, 0, -1);
   glVertex3f(0, 0, 1);
   glEnd();
}