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

    bluetooth = new QBluetoothDeviceDiscoveryAgent;
    ui->scanButton->setEnabled(false);
    QFont font = ui->bluetoothStatusLabel->font();
    //font.setBold(true);
    font.setPointSize(20);
    ui->bluetoothStatusLabel->setFont(font);
    font.setPointSize(25);
    ui->listWidget->setFont(font);
    ui->bluetoothStatusLabel->setText("Scanning...");
    connect(bluetooth,SIGNAL(finished()),this,SLOT(setScanButtonEnabled()));
    connect(bluetooth,SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),this,SLOT(newDeviceFound(QBluetoothDeviceInfo)));
    bluetooth->start();
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

void MainWindow::newDeviceFound(QBluetoothDeviceInfo btInfo)
{
//    QListWidgetItem* item = new QListWidgetItem(btInfo.name());
 //   item->setData(Qt::UserRole,btInfo.address().toString());
 //   ui->listWidget->addItem(item);
    qDebug() <<  btInfo.address();
    qDebug() <<  btInfo.name();
    qDebug() <<  btInfo.rssi();

    QList<QListWidgetItem *> items = ui->listWidget->findItems(btInfo.name(), Qt::MatchExactly);
    if (items.empty()) {
        QListWidgetItem *item = new QListWidgetItem(btInfo.name());
        item->setData(Qt::UserRole,btInfo.address().toString());
        QBluetoothLocalDevice::Pairing pairingStatus = localDevice->pairingStatus(btInfo.address());
//        if (pairingStatus == QBluetoothLocalDevice::Paired || pairingStatus == QBluetoothLocalDevice::AuthorizedPaired )
//            item->setTextColor(QColor(Qt::green));
//        else
//            item->setTextColor(QColor(Qt::red));

        ui->listWidget->addItem(item);
    }
}

void MainWindow::on_disconnectButton_clicked()
{

}

void MainWindow::on_scanButton_clicked()
{
    ui->scanButton->setEnabled(false);
    ui->listWidget->clear();
    ui->bluetoothStatusLabel->setText("Scanning...");
    bluetooth->start();
}

void MainWindow::setScanButtonEnabled()
{
    ui->scanButton->setEnabled(true);
    ui->bluetoothStatusLabel->setText("");
}

void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    QString name = index.data(Qt::EditRole).toString();
    QString address = index.data(Qt::UserRole).toString();
    QBluetoothAddress adapterAddress = localDevice->address();
    discoveryAgent = new QBluetoothServiceDiscoveryAgent(QBluetoothAddress(adapterAddress));
    discoveryAgent->setRemoteAddress(QBluetoothAddress(address));
   // localDevice->requestPairing(QBluetoothAddress(address),QBluetoothLocalDevice::Paired);
    qDebug() << name << " " << address;
}
