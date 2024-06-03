#include "antorcha.h"
#include <QTimer>
#include <QGraphicsScene>
#include <cmath>
#include "casa.h"
#include "game.h"

Antorcha::Antorcha(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent), vx(60), vy(0), t(0), g(9.8) {
    setPixmap(QPixmap(":proyectiles/pr/antorchaof").scaled(70, 70));

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void Antorcha::setInitialVelocity(float vx, float vy) {
    this->vx = vx;
    this->vy = vy;
}

void Antorcha::setInitialVelocityWithAngle(float velIn, float theta) {
    theta = theta * M_PI / 180.0;
    vx = velIn * cos(theta);
    vy = -velIn * sin(theta);
}

void Antorcha::move() {
    qDebug() << "Antorcha moviéndose...";
    const float dt = 0.1;



    float posX = x() + (vx * dt);
    float posY = y() + (vy * dt) + (0.5 * g * dt * dt);

    vy += g * dt;

    setPos(posX, posY);

    QList<QGraphicsItem *> collidingItems = scene()->collidingItems(this);
    for (QGraphicsItem *item : collidingItems) {
        Casa *casa = dynamic_cast<Casa *>(item);
        if (casa) {
            scene()->removeItem(casa);
            delete casa;

            qDebug() << "Colisión detectada, emitiendo señal...";


            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    if (posY >= scene()->height()) {
        QTimer *timer = qobject_cast<QTimer*>(sender());
        if (timer) {
            timer->stop();
            deleteLater();
        }
    }
}
