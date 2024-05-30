#include "personaje.h"
#include "flecha.h"
#include "antorcha.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QTimer>

Personaje::Personaje(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent), shootDirectionRight(true), canShoot(true) {
    setPixmap(QPixmap("C:/Users/juana/Downloads/Vikings/Viking2/Run/1.png"));
}

void Personaje::shootFlecha() {
    if (canShoot) {
        Flecha *flecha = new Flecha(shootDirectionRight);
        flecha->setPos(x() + pixmap().width() / 2, y() + pixmap().height() / 2);
        scene()->addItem(flecha);

        shootDirectionRight = !shootDirectionRight;
        canShoot = false;

        QTimer::singleShot(1000, this, &Personaje::enableShoot);
    }
}

void Personaje::shootAntorcha() {
    if (canShoot) {
        Antorcha *antorcha = new Antorcha();
        antorcha->setPos(x() + pixmap().width() / 2, y() + pixmap().height() / 2);
        scene()->addItem(antorcha);

        if (shootDirectionRight) {
            antorcha->setInitialVelocityWithAngle(60, 45);
        } else {
            antorcha->setInitialVelocityWithAngle(60, 135);
        }

        shootDirectionRight = !shootDirectionRight;
        canShoot = false;

        QTimer::singleShot(1000, this, &Personaje::enableShoot);
    }
}

void Personaje::enableShoot() {
    canShoot = true;
}
