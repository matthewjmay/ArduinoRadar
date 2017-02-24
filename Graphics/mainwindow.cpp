#include "mainwindow.h"
#include "drawclass.h"
#include <QWidget>
#include <QtSerialPort/QtSerialPort>
#include <QSerialPort>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setGeometry(0, 0, 100, 110);
    QPalette pal = palette();

    // set black background
    pal.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);
    setPalette(pal);

    QPainter painter(this);
    painter.setPen(Qt::green);

    painter.drawLine(0,100,100,100);

    QRectF rectangle(0, 0, 100, 100);
    int startAngle = 180 * 16;
    int spanAngle = 0;
    painter.drawArc(rectangle, startAngle, spanAngle);

    painter.drawLine(50,100,50,0);

    input = new QSerialPort(this);
    bool success = input->open(QIODevice::ReadOnly);
    if (!success)
        qDebug() << "opening failed";
    else
        connect(input, SIGNAL(readyRead()), this, SLOT(radarEvent());
}

MainWindow::radarEvent()
{
    QByteArray raw = input->readAll();
    QString convert = raw;
    QStringList list = convert.split('.', QString::SkipEmptyParts);
    drawClass(list.at(0), list.at(1), this);
}
