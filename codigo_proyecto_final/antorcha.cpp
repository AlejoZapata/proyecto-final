#include "antorcha.h"
#include <QTimer>
#include <QGraphicsScene>

Antorcha::Antorcha(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent), vx(0), vy(0), t(0) {
    setPixmap(QPixmap("C:/Users/juana/Downloads/antorcha.png"));

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void Antorcha::setInitialVelocity(float vx, float vy) {
    this->vx = vx;
    this->vy = vy;
}

void Antorcha::move() {
    t += 0.05;  // Incrementar el tiempo

    // Movimiento parabólico
    float x = vx * t;
    float y = vy * t - 0.5 * 9.8 * t * t;
    setPos(pos().x() + x, pos().y() - y);

    // Eliminar antorcha si sale de la escena
    if (pos().y() > 600 || pos().x() > 800) {
        scene()->removeItem(this);
        delete this;
    }
}
