#include "personaje.h"
#include "flecha.h"
#include "antorcha.h"
#include <QKeyEvent>
#include <QGraphicsScene>


Personaje::Personaje(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent), shootDirectionRight(true) {
    setPixmap(QPixmap("C:/Users/juana/Downloads/Vikings/Viking2/Run/1.png"));
}

void Personaje::shootFlecha() {
    Flecha *flecha = new Flecha();
    flecha->setPos(x() + pixmap().width() / 2, y() + pixmap().height() / 2);
    scene()->addItem(flecha);
}

void Personaje::shootAntorcha() {
    Antorcha *antorcha = new Antorcha();
    antorcha->setPos(x() + pixmap().width() / 2, y() + pixmap().height() / 2);
    scene()->addItem(antorcha);

    if (shootDirectionRight) {
        antorcha->setInitialVelocityWithAngle(60, 45);
    } else {
        antorcha->setInitialVelocityWithAngle(60, 135);
    }

    shootDirectionRight = !shootDirectionRight;
}
