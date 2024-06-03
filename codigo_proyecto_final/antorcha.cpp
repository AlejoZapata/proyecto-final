#include "antorcha.h"
#include <QTimer>
#include <QGraphicsScene>
#include <cmath>
#include "casa.h"
#include "game.h"
using namespace std;

Antorcha::Antorcha(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent), vx(60), vy(0), t(0), g(9.8) {
    setPixmap(QPixmap(":proyectiles/pr/antorchaof").scaled(70, 70));

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);

    logFile.open("simulacion_antorcha.log", ios::out | ios::app);
    logEvent("Antorcha creada con velocidad inicial vx: " + to_string(vx) + ", vy: " + to_string(vy));
}

void Antorcha::setInitialVelocity(float vx, float vy) {
    this->vx = vx;
    this->vy = vy;
    logEvent("Velocidad inicial establecida: vx: " + to_string(vx) + ", vy: " + to_string(vy));
}

void Antorcha::setInitialVelocityWithAngle(float velIn, float theta) {
    theta = theta * M_PI / 180.0;
    vx = velIn * cos(theta);
    vy = -velIn * sin(theta);
    logEvent("Velocidad inicial con ángulo establecida: velocidad: " + to_string(velIn) + ", ángulo: " + to_string(theta));
}

void Antorcha::move() {
    const float dt = 0.1;
    float posX = x() + (vx * dt);
    float posY = y() + (vy * dt) + (0.5 * g * dt * dt);

    vy += g * dt;

    setPos(posX, posY);
    logEvent("Moviendo antorcha a posición: (" + to_string(posX) + ", " + to_string(posY) + ")");

    QList<QGraphicsItem *> collidingItems = scene()->collidingItems(this);
    for (QGraphicsItem *item : collidingItems) {
        Casa *casa = dynamic_cast<Casa *>(item);
        if (casa) {
            scene()->removeItem(casa);
            delete casa;
            logEvent("Colisión detectada con Casa en posición: (" + to_string(posX) + ", " + to_string(posY) + ")");
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
        logEvent("Antorcha ha salido de los límites de la escena en y: " + to_string(posY));
    }
}

void Antorcha::logEvent(const string &message) {
    if (logFile.is_open()) {
        logFile << message << endl;
    }
}
