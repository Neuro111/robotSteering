#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSensors/QAccelerometer>
#include <QTimer>
#include <QDebug>
#include <QtMath>
#include <QtBluetooth/QtBluetooth>

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
    QBluetoothDeviceDiscoveryAgent *bluetooth;
    QBluetoothLocalDevice *localDevice;
    QBluetoothServiceDiscoveryAgent *discoveryAgent;

private slots:
    void readAccel();
    void newDeviceFound(QBluetoothDeviceInfo btInfo);
    void on_disconnectButton_clicked();
    void on_scanButton_clicked();
    void setScanButtonEnabled();
    void on_listWidget_doubleClicked(const QModelIndex &index);
};

#endif // MAINWINDOW_H
