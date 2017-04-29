#include "mainwindow.h"
#include "radarLine.h"
#include <QWidget>
#include <QtSerialPort/QtSerialPort>
#include <QSerialPort>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // set black background
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);
    setPalette(pal);

    input = new QSerialPort("COM6", this);

    //if serial port does not automatically configure, uncomment below
    /*
    input->setBaudRate(QSerialPort::Baud9600);
    input->setFlowControl(QSerialPort::NoFlowControl);
    input->setParity(QSerialPort::NoParity);
    input->setDataBits(QSerialPort::Data8);
    input->setStopBits(QSerialPort::OneStop);
    */
    bool success = input->open(QIODevice::ReadOnly);
    if (!success)
        qDebug() << "Error: "<< input->error() << " " << input->errorString() << endl;
    else
        input->clear();
        //connect serial port readyRead to radar event
        connect(input, &QSerialPort::readyRead, this, &MainWindow::radarEvent);
}

void MainWindow::paintEvent(QPaintEvent * /* event */ ){

    QPainter painter(this);
    painter.setPen(Qt::green);

    //Draw outer arc
    QRectF rectangle(QPointF(0, 0), QPointF(width(), height()*2 - height()/15));
    int startAngle = 0;
    int spanAngle = 180*16;

    painter.drawArc(rectangle, startAngle, spanAngle);
    painter.translate(width()/2, height()-height()/30);

    //Draw radar lines
    for (int i =0; i<=180/30; ++i){
        painter.drawLine(0, 0, width()/2, 0);
        painter.rotate(-30);
    }
}

void MainWindow::radarEvent()
{
    QByteArray raw = input->readAll();
    QString convert = raw;

    QStringList list = convert.split('.', QString::SkipEmptyParts);
    if (list.size()==2)
        new radarLine((list.at(0)).simplified(), (list.at(1)).simplified(), this);
    else
        qDebug() << "Unreadable serial data" << endl;
}

