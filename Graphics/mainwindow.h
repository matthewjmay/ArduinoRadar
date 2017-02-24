#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class QMainWindow;
//class QPushButton;
class QSerialDevice;
class QImage;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

private:
    //QPushButton *start;
    QSerialDevice *input;

private slots:
    //void startTransmission();
    void radarEvent();
};

#endif // MAINWINDOW_H
