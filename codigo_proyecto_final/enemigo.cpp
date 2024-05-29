#include "enemigo.h"
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h>

Enemigo::Enemigo(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap("C:/Users/juana/Downloads/Vikings/Viking3/Alert1H/4.png"));

    setPos(500, 100); // x = 100, y = 50 (ajusta según sea necesario)

    vx = -3;

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void Enemigo::move() {
    const int sueloPosY = 500;

    setPos(x() + vx, y());

    if (pos().y() >= sueloPosY) {
        return;
    }

    // Eliminar el enemigo si sale de la escena
    if (pos().y() > 600 || pos().x() < -pixmap().width()) {
        scene()->removeItem(this);
        delete this;
    }
}
