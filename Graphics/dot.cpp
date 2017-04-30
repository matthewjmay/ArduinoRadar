#include "dot.h"
#include <QtGui>
#include <QTimer>

dot::dot(int distance, int rotation, QWidget *parent) : QWidget(parent)
{
    startColor = Qt::red;
    currentAlpha = 255;

    angle = rotation;
    totduration = 30000;
    colorChangeTime = 333;
    resize(parent->size());
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::transparent);
    setAutoFillBackground(true);
    setPalette(pal);
    setAttribute(Qt::WA_DeleteOnClose);
    firstpaint = true;

    dist = (width()/2) * (distance/70.0);

    timer = new QTimer(this);
    timer -> start(colorChangeTime);
    connect(timer, &QTimer::timeout, this, static_cast<void (dot::*)()>(&dot::update));

    show();
}

void dot::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.translate(width()/2, height()-height()/30);
    painter.rotate(-angle);

    QColor semiTransparentColor = startColor;
    semiTransparentColor.setAlpha(currentAlpha);
    painter.setPen(QPen(semiTransparentColor, 3));
    painter.drawEllipse (QPoint(dist, 0), 6, 6);
    currentAlpha -= 255 * (double (timer->interval()) / totduration);
    if (currentAlpha <= 0) {
        timer->stop();
        close();
    }
}

