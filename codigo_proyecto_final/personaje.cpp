#include "personaje.h"
#include "flecha.h"
#include "antorcha.h"
#include <QKeyEvent>
#include <QGraphicsScene>


Personaje::Personaje(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap("C:/Users/juana/Downloads/Vikings/Viking2/Run/1.png"));
}

void Personaje::shootFlecha() {
    Flecha *flecha = new Flecha();
    // Disparar desde la posición actual del personaje
    flecha->setPos(x() + pixmap().width() / 2, y() + pixmap().height() / 2);
    scene()->addItem(flecha);
}

void Personaje::shootAntorcha() {
    Antorcha *antorcha = new Antorcha();
    // Disparar desde la posición actual del personaje
    antorcha->setPos(x() + pixmap().width() / 2, y() + pixmap().height() / 2);
    scene()->addItem(antorcha);
}
