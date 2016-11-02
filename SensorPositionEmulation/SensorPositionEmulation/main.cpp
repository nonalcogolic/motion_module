#include "sensorpositionemulation.h"
#include "OpenGLGraphicalWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   
    
    COpenGLGraphicalWidget openGl;
    //openGl.resize(300, 300);
    openGl.show();
    openGl.paintGL();

    return a.exec();
}
