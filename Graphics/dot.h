#ifndef DOT_H
#define DOT_H

#include <QWidget>

class QPainter;
class dot : public QWidget
{
    Q_OBJECT

public:
    dot(int distance, int rotation, QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QTimer *timer;
    bool firstpaint;
    int currentAlpha;
    QColor startColor;
    int colorChangeTime;
    int totduration;
    int angle;
    double dist;
};

#endif // DOT_H
