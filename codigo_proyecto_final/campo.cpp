#include "campo.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QVector2D>
#include "enemigo.h"
#include "enemigo2.h"
#include "personaje.h"
#include <string>

using namespace std;

Campo::Campo(Personaje *personaje, QGraphicsItem *parent)
    : QObject(), QGraphicsEllipseItem(parent), personaje(personaje) {
    setRect(-150, -150, 1000, 1000);

    QBrush brush(Qt::blue, Qt::Dense4Pattern);
    brush.setColor(QColor(0, 0, 255, 0));
    setBrush(brush);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(affectEnemies()));
    timer->start(100);

    logFile.open("simulacion_campo.log", ios::out | ios::app);
    logEvent("Campo creado alrededor del personaje.");
}

void Campo::affectEnemies() {
    QList<QGraphicsItem *> items = scene()->items();
    for (QGraphicsItem *item : items) {
        if (typeid(*item) == typeid(Enemigo) || typeid(*item) == typeid(Enemigo2)) {
            if (personaje->collidesWithItem(item)) {
                emit enemyReachedMidpoint();
                logEvent("Enemigo alcanzó el punto medio.");
            }

            QPointF enemyPos = item->pos();
            QPointF center = personaje->pos();

            QVector2D direction(center - enemyPos);
            direction.normalize();

            float attractionSpeed = 2.0f;
            QPointF displacement = direction.toPointF() * attractionSpeed;

            item->setPos(enemyPos + displacement);
            logEvent("Moviendo enemigo hacia el personaje a posición: (" + to_string(enemyPos.x()) + ", " + to_string(enemyPos.y()) + ")");
        }
    }
}

void Campo::logEvent(const string &message) {
    if (logFile.is_open()) {
        logFile << message << endl;
    }
}
