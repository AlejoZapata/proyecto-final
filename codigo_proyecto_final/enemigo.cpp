#include "enemigo.h"
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h>

Enemigo::Enemigo(bool shouldMove, QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent), vx(-3), shouldMove(shouldMove) {
    QPixmap originalPixmap(":enemigos/enem/enemigo");
    QPixmap scaledPixmap = originalPixmap.scaled(200, 200, Qt::KeepAspectRatio);
    setPixmap(scaledPixmap);

    setPos(500, 300);

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void Enemigo::move() {
    if (!shouldMove) {
        return;
    }

    const int sueloPosY = 500;

    setPos(x() + vx, y());

    if (pos().y() >= sueloPosY) {
        return;
    }


    if (pos().y() > 600 || pos().x() < -pixmap().width()) {
        emit enemyOutOfBounds();
        scene()->removeItem(this);
        delete this;
    }
}
