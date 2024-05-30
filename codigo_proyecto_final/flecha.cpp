#include "flecha.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "enemigo.h"
#include "enemigo2.h"
#include <cmath>

Flecha::Flecha(bool directionRight, QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent), directionRight(directionRight) {
    QPixmap pixmap;
    if (directionRight) {
        pixmap.load("C:/Users/juana/Downloads/hacharigh-removebg-preview.png");
    } else {
        pixmap.load("C:/Users/juana/Downloads/hacha-removebg-preview.png");
    }

    QPixmap scaledPixmap = pixmap.scaled(140, 140, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(scaledPixmap);

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void Flecha::move() {
    qreal angle = 0.0;
    if (directionRight) {
        setPos(x() + 10, y());
        angle = 45.0;
    } else {
        setPos(x() - 10, y());
        angle = -45.0;
    }

    if (pos().x() > scene()->width() || pos().x() < 0) {
        scene()->removeItem(this);
        delete this;
        return;
    }


    setTransformOriginPoint(pixmap().width() / 2, pixmap().height() / 2);
    setRotation(rotation() + angle);

    QList<QGraphicsItem *> collidingItems = this->collidingItems();
    for (QGraphicsItem *item : collidingItems) {
        if (typeid(*item) == typeid(Enemigo) || typeid(*item) == typeid(Enemigo2)) {
            scene()->removeItem(item);
            scene()->removeItem(this);
            delete item;
            delete this;
            return;
        }
    }
}
