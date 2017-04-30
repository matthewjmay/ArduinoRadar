#ifndef RADARLINE_H
#define RADARLINE_H

#include <QWidget>
class QPainter;

class radarLine : public QWidget
{
    Q_OBJECT

public:
    radarLine(QString const &distance, QString const &motorpos, QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);

private:
    QTimer *timer;
    QColor startColor;
    QPainter *painter;
    bool firstpaint;
    int currentAlpha;
    int colorChangeTime;
    int dist;
    int totduration;
    int rotation;
};

#endif // RADARLINE_H
