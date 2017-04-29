#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

//class QPushButton;
class QSerialPort;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

private:
    //QPushButton *start;
    QSerialPort *input;

protected:
    void paintEvent(QPaintEvent*);

private slots:
    //void startTransmission();
    void radarEvent();
};

#endif // MAINWINDOW_H
