#include "antorcha.h"
#include <QTimer>
#include <QGraphicsScene>
#include <cmath>

Antorcha::Antorcha(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent), vx(60), vy(0), t(0), g(9.8) {
    setPixmap(QPixmap("C:/Users/juana/Downloads/pngegg.png").scaled(100, 100));

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void Antorcha::setInitialVelocity(float velIn, float theta) {

    theta = theta * M_PI / 180.0;


    vx = velIn * cos(theta);
    vy = -velIn * sin(theta);
}

void Antorcha::move() {
    const float dt = 0.1;

    float posX = x() + (vx * dt);
    float posY = y() + (vy * dt) + (0.5 * g * dt * dt);

    vy += g * dt;

    setPos(posX, posY);

    if (posY >= scene()->height()) {
        QTimer *timer = qobject_cast<QTimer*>(sender());
        if (timer) {
            timer->stop();
            deleteLater();
        }
    }
}
