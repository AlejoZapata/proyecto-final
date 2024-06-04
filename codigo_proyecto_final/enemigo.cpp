#include "enemigo.h"
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h>
Enemigo::Enemigo(bool shouldMove, QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent), vx(-3), shouldMove(shouldMove), spriteIndex(0) {
    int newWidth = 200;
    int newHeight = 200;

    for (int i = 0; i <= 19; i++) {
        QString imagePath = QString(":enemigo1/enem/2/%0.png").arg(i);
        QPixmap pixmap(imagePath);
        QPixmap scaledPixmap = pixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio);
        sprites.append(scaledPixmap);
    }

    setPixmap(sprites.at(spriteIndex));

    setPos(500, 300);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Enemigo::move);
    timer->start(50);
}

void Enemigo::move() {
    spriteIndex = (spriteIndex + 1) % sprites.size();
    setPixmap(sprites.at(spriteIndex));

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

