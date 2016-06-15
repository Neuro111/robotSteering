#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSensors/QAccelerometer>
#include <QTimer>
#include <QDebug>
#include <QtMath>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QAccelerometer *accel;
    QTimer *t1;
    QAccelerometerReading *readings;

private slots:
    void readAccel();
};

#endif // MAINWINDOW_H
