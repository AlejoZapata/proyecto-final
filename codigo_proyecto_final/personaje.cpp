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

    flecha->setPos(150, 350);
    scene()->addItem(flecha);
}

void Personaje::shootAntorcha() {
    Antorcha *antorcha = new Antorcha();
    antorcha->setPos(150,300);
    scene()->addItem(antorcha);
}
