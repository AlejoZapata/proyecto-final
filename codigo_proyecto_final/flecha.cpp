#include "flecha.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "enemigo.h"

Flecha::Flecha(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap("C:/Users/juana/Downloads/xd.png"));

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void Flecha::move() {
    // Mover la flecha hacia arriba
    setPos(x(), y() - 10);

    // Eliminar flecha si sale de la escena
    if (pos().y() + pixmap().height() < 0) {
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
