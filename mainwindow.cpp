#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    accel = new QAccelerometer();
    accel->setAccelerationMode(QAccelerometer::Gravity);
    accel->setDataRate(10);

    accel->setActive(true);
    accel->start();

    connect(accel,SIGNAL(readingChanged()),SLOT(readAccel()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readAccel()
{
    double x = accel->reading()->x();
    double y = accel->reading()->y();
    double z = accel->reading()->z();

    ui->xLabel->setText(QString::number(x));
    ui->yLabel->setText(QString::number(y));
    ui->zLabel->setText(QString::number(z));

    double pitch = atan2(-y,z) * 57.2957795;
    double roll = -atan2(x,sqrt(y*y + z*z)) * 57.2957795;
    ui->pitchLabel->setText(QString::number(pitch));
    ui->rollLabel->setText(QString::number(roll));
}
