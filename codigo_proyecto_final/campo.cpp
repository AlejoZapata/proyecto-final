#include "campo.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QVector2D>
#include "enemigo.h"
#include "enemigo2.h"


Campo::Campo(QGraphicsItem *parent) : QObject(), QGraphicsEllipseItem(parent) {
    setRect(50, -100, 500, 500);
    setBrush(QBrush(Qt::blue, Qt::Dense4Pattern));

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(affectEnemies()));
    timer->start(100);
}

void Campo::affectEnemies() {
    QPointF center = boundingRect().center();

    QList<QGraphicsItem *> items = collidingItems();
    for (QGraphicsItem *item : items) {
        if (typeid(*item) == typeid(Enemigo) || typeid(*item) == typeid(Enemigo2)) {
            QPointF enemyPos = item->pos();

            QVector2D direction(center - enemyPos);

            direction.normalize();

            float attractionSpeed = 2.0f;

            QPointF displacement = direction.toPointF() * attractionSpeed;

            item->setPos(enemyPos + displacement);
        }
    }
}
