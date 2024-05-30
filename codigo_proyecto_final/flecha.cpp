#include "flecha.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "enemigo.h"

Flecha::Flecha(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent) {
    QPixmap pixmap("C:/Users/juana/Downloads/pngimg.com - arrow_bow_PNG37.png");
    QPixmap scaledPixmap = pixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(scaledPixmap);

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void Flecha::move() {
    setPos(x() + 10, y());

    if (pos().x() > scene()->width()) {
        scene()->removeItem(this);
        delete this;
        return;
    }

    // Comprobar colisiones con enemigos
    QList<QGraphicsItem *> collidingItems = this->collidingItems();
    for (QGraphicsItem *item : collidingItems) {
        if (typeid(*item) == typeid(Enemigo)) {
            scene()->removeItem(item);
            scene()->removeItem(this);
            delete item;
            delete this;
            return;
        }
    }
}
