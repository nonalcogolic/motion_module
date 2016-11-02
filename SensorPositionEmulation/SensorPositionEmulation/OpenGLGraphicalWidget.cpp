#include "OpenGLGraphicalWidget.h"



COpenGLGraphicalWidget::COpenGLGraphicalWidget(QWidget *parent) // конструктор
   : QGLWidget(parent)
   , xRotation (0)
	, yRotation (0)
	, zRotation (0)
	, scale (1)
{
 //  resizeGL(200, 200); // задаем размеры окна
   resize(200, 200);
}


COpenGLGraphicalWidget::~COpenGLGraphicalWidget()
{

}


void COpenGLGraphicalWidget::initializeGL()
{
   qglClearColor(Qt::white); // заполняем экран белым цветом
   glEnable(GL_DEPTH_TEST); // задаем глубину проверки пикселей
   glShadeModel(GL_FLAT); // убираем режим сглаживания цветов
   glEnable(GL_CULL_FACE); // говорим, что будем строить только внешние поверхности
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // фигуры будут закрашены с обеих сторон
}

void COpenGLGraphicalWidget::resizeGL(int nWidth, int nHeight)
{
   glViewport(0, 0, nHeight, nHeight); // установка точки обзора
   glMatrixMode(GL_PROJECTION); // установка режима матрицы
   glLoadIdentity(); // загрузка матрицы
   
}

void COpenGLGraphicalWidget::paintGL() // рисование
{

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка экрана
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();           // загрузка единичную матрицу



	// glRotatef(25, 0.0f, 1.0f, 0.0f); // поворот по X
	 glRotatef(20, 1.0f, 1.0f, 0.0f); // поворот по Y
   drawAxises();

   glScalef(scale, scale, scale);
   glRotatef(xRotation, 1.0f, 0.0f, 0.0f); // поворот по X
   glRotatef(yRotation, 0.0f, 1.0f, 0.0f); // поворот по Y
   glRotatef(zRotation, 0.0f, 0.0f, 1.0f); // поворот по Z


  

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

 

void COpenGLGraphicalWidget::mousePressEvent(QMouseEvent* pe) // нажатие клавиши мыши
{
	mousePos = pe->pos();
}
void COpenGLGraphicalWidget::mouseMoveEvent(QMouseEvent* pe) // изменение положения стрелки мыши
{
	xRotation += 180 / scale*(GLfloat)(pe->y() - mousePos.y()) / height(); // вычисляем углы поворота
	zRotation += 180 / scale*(GLfloat)(pe->x() - mousePos.x()) / width();

	mousePos = pe->pos();

	updateGL(); // обновляем изображение
}
void COpenGLGraphicalWidget::mouseReleaseEvent(QMouseEvent *pe)
{
}
void COpenGLGraphicalWidget::wheelEvent(QWheelEvent* pe) // вращение колёсика мыши
{
	// если колесико вращаем вперед -- умножаем переменную масштаба на 1.1
	// иначе -- делим на 1.1
	if ((pe->delta())>0) scale *= 1.1; else if ((pe->delta())<0) scale /= 1.1;

	updateGL();
}