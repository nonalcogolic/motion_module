#include "OpenGLGraphicalWidget.h"



COpenGLGraphicalWidget::COpenGLGraphicalWidget(QWidget *parent) // конструктор
   : QGLWidget(parent)
{
   resizeGL(200, 200); // задаем размеры окна
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
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();           // загрузка единичную матрицу

  
  // glScalef(0.1, 0.1, 0.1);
  
  // glRotatef(20, 1, 1, 0);
 //  glRotatef(90, 0, 0, 1);
   drawAxises();

   drawSensor();
 
}

void COpenGLGraphicalWidget::
drawAxises()
{
   glRotatef(20, 1, 0, 0);
   glRotatef(40, 0, 1, 0);
  // glRotatef(90, 0, 0, 1);
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


void COpenGLGraphicalWidget::
drawSensor()
{
  
   QColor axisColor(0, 100, 0, 255);
   qglColor(axisColor);
   glBegin(GL_QUADS);
   glVertex3f(-0.5, 0.5, 0);
   glVertex3f(-0.5, -0.5, 0);
   glVertex3f(0.5, -0.5, 0);
   glVertex3f(0.5, 0.5, 0);
   glEnd();
}