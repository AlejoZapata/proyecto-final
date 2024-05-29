#include "personaje.h"
#include "flecha.h"
#include "antorcha.h"
#include <QKeyEvent>
#include <QGraphicsScene>


Personaje::Personaje(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap("C:/Users/juana/Downloads/Vikings/Viking2/Run/1.png"));
}

void Personaje::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Q) {

        shootFlecha();
    }
}

void Personaje::shootFlecha() {
    Flecha *flecha = new Flecha();
    // Ajustar la posición de la flecha para que se dispare desde la parte derecha del personaje
    flecha->setPos(x() + pixmap().width(), y() + pixmap().height() / 2 - flecha->pixmap().height() / 2);
    scene()->addItem(flecha);
}
void Personaje::shootAntorcha() {
    Antorcha *antorcha = new Antorcha();
    scene()->addItem(antorcha);
}
