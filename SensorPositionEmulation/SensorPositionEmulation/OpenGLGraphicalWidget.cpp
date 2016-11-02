#include "OpenGLGraphicalWidget.h"



COpenGLGraphicalWidget::COpenGLGraphicalWidget(QWidget *parent) // �����������
   : QGLWidget(parent)
   , xRotation (0)
	, yRotation (0)
	, zRotation (0)
	, scale (1)
{
 //  resizeGL(200, 200); // ������ ������� ����
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



	// glRotatef(25, 0.0f, 1.0f, 0.0f); // ������� �� X
	 glRotatef(20, 1.0f, 1.0f, 0.0f); // ������� �� Y
   drawAxises();

   glScalef(scale, scale, scale);
   glRotatef(xRotation, 1.0f, 0.0f, 0.0f); // ������� �� X
   glRotatef(yRotation, 0.0f, 1.0f, 0.0f); // ������� �� Y
   glRotatef(zRotation, 0.0f, 0.0f, 1.0f); // ������� �� Z


  

   drawSensor();
 
}

void COpenGLGraphicalWidget::
drawAxises()
{

	
//   glRotatef(80, 1, 1, 0);
 //  glRotatef(40, 0, 1, 0);
   //glRotatef(0, 0, 0, 1);
   QColor axisColor(0, 0, 0, 255);
   qglColor(axisColor);
   glBegin(GL_LINES);
   glVertex3f(0, -0.8, 0);
   glVertex3f(0, 0.8, 0);
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


void COpenGLGraphicalWidget::
drawSensor()
{
  
   QColor bkGround(0, 0, 100, 255);
   qglColor(bkGround);
   glBegin(GL_QUADS);
   glVertex3f(-0.4, -0.01, -0.2);
   glVertex3f(-0.4, -0.01, -0.4);
   glVertex3f(-0.2, -0.01, -0.4);
   glVertex3f(-0.2, -0.01, -0.2);
   glEnd();


   glBegin(GL_QUADS);
   glVertex3f(0.3, -0.01, 0.2);
   glVertex3f(0.3, -0.01, 0.4);
   glVertex3f(0.2, -0.01, 0.4);
   glVertex3f(0.2, -0.01, 0.2);
   glEnd();

   glBegin(GL_QUADS);
   glVertex3f(0.1, -0.01, -0.2);
   glVertex3f(0.1, -0.01, -0.3);
   glVertex3f(0.2, -0.01, -0.3);
   glVertex3f(0.2, -0.01, -0.2);
   glEnd();

   QColor frontGround(0, 100, 0, 255);
   qglColor(frontGround);
   glBegin(GL_QUADS);
   glVertex3f(-0.5, 0.01, 0.5);
   glVertex3f(-0.5, 0.01, -0.5);
   glVertex3f(0.5, 0.01, -0.5);
   glVertex3f(0.5, 0.01, 0.5);
   glEnd();
}

 

void COpenGLGraphicalWidget::mousePressEvent(QMouseEvent* pe) // ������� ������� ����
{
	mousePos = pe->pos();
}
void COpenGLGraphicalWidget::mouseMoveEvent(QMouseEvent* pe) // ��������� ��������� ������� ����
{
	xRotation += 180 / scale*(GLfloat)(pe->y() - mousePos.y()) / height(); // ��������� ���� ��������
	zRotation += 180 / scale*(GLfloat)(pe->x() - mousePos.x()) / width();

	mousePos = pe->pos();

	updateGL(); // ��������� �����������
}
void COpenGLGraphicalWidget::mouseReleaseEvent(QMouseEvent *pe)
{
}
void COpenGLGraphicalWidget::wheelEvent(QWheelEvent* pe) // �������� ������� ����
{
	// ���� �������� ������� ������ -- �������� ���������� �������� �� 1.1
	// ����� -- ����� �� 1.1
	if ((pe->delta())>0) scale *= 1.1; else if ((pe->delta())<0) scale /= 1.1;

	updateGL();
}