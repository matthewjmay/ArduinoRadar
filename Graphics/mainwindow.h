#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

//class QPushButton;
class QSerialPort;
class serialPortDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

private:
    //QPushButton *start;
    QSerialPort *input;
    serialPortDialog *getname;

protected:
    void paintEvent(QPaintEvent*);

private slots:
    void openport(const QString&);
    void radarEvent();
signals:
    void invalidport(const QString& portname);
};

#endif // MAINWINDOW_H
