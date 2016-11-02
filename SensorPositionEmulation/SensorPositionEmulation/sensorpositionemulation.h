#ifndef SENSORPOSITIONEMULATION_H
#define SENSORPOSITIONEMULATION_H

#include <QtWidgets/QWidget>
#include "ui_sensorpositionemulation.h"

class SensorPositionEmulation : public QWidget
{
    Q_OBJECT

public:
    SensorPositionEmulation(QWidget *parent = 0);
    ~SensorPositionEmulation();

private:
    Ui::SensorPositionEmulationClass ui;
};

#endif // SENSORPOSITIONEMULATION_H
