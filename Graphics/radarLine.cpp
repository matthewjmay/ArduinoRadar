#include "radarLine.h"
#include "dot.h"
#include <QtGui>
#include <QTimer>

radarLine::radarLine(const QString &distance, const QString &motorpos, QWidget *parent) : QWidget(parent)
{
    startColor = Qt::green;
    rotation = motorpos.toInt();
    dist = distance.toInt();
    currentAlpha = 255;
    colorChangeTime = 333;
    totduration = 10000;
    setAttribute(Qt::WA_DeleteOnClose);
    resize(parent->size());
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::transparent);
    setAutoFillBackground(true);
    setPalette(pal);
    firstpaint = true;

    //connect timer timeout to colour change (fading)
    timer = new QTimer(this);
    timer -> start(colorChangeTime);
    connect(timer, &QTimer::timeout, this, static_cast<void (radarLine::*)()>(&radarLine::update));

    //create radar dot if in range
    if (dist > 0 && dist < 70)
        new dot(dist, rotation, parent);

    show();
}

void radarLine::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.translate(width()/2, height()-height()/30);
    painter.rotate(-rotation);

    QColor semiTransparentColor = startColor;
    semiTransparentColor.setAlpha(currentAlpha);
    painter.setPen(QPen(semiTransparentColor, 3));
    painter.drawLine(0, 0, width()/2, 0);
    currentAlpha -= 255 * (double (timer->interval()) / totduration);
    if (currentAlpha <= 0) {
        timer->stop();
        close();
    }
}
