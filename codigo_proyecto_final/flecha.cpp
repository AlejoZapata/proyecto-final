#include "flecha.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "enemigo.h"
#include "enemigo2.h"
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

Flecha::Flecha(bool directionRight, QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent), directionRight(directionRight), angle(0.0) {
    QPixmap pixmap;
    if (directionRight) {
        pixmap.load(":proyectiles/pr/hachaderecha");
    } else {
        pixmap.load(":proyectiles/pr/hachaiz");
    }

    QPixmap scaledPixmap = pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(scaledPixmap);

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);

    logFile.open("simulacion_flecha.log", ios::out | ios::app);
    logEvent("Flecha creada en dirección " + string(directionRight ? "derecha" : "izquierda"));
}

void Flecha::move() {
    if (directionRight) {
        setPos(x() + 10, y());
        angle += 45.0;
    } else {
        setPos(x() - 10, y());
        angle -= 45.0;
    }

    if (pos().x() > scene()->width() || pos().x() < 0) {
        logEvent("Flecha salió de los límites de la escena.");
        scene()->removeItem(this);
        delete this;
        return;
    }

    setTransformOriginPoint(pixmap().width() / 2, pixmap().height() / 2);
    setRotation(rotation() + angle);

    logEvent("Flecha movida a posición: (" + to_string(pos().x()) + ", " + to_string(pos().y()) + ") con ángulo: " + to_string(angle));

    QList<QGraphicsItem *> collidingItems = this->collidingItems();
    for (QGraphicsItem *item : collidingItems) {
        if (typeid(*item) == typeid(Enemigo) || typeid(*item) == typeid(Enemigo2)) {
            logEvent("Flecha colisionó con enemigo en posición: (" + to_string(item->pos().x()) + ", " + to_string(item->pos().y()) + ")");
            scene()->removeItem(item);
            scene()->removeItem(this);
            delete item;
            delete this;
            return;
        }
    }
}

void Flecha::logEvent(const string &message) {
    if (logFile.is_open()) {
        logFile << message << endl;
    }
}
