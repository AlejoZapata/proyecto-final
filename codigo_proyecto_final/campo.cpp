#include "campo.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QVector2D>
#include "enemigo.h"

Campo::Campo(QGraphicsItem *parent) : QObject(), QGraphicsEllipseItem(parent) {
    setRect(100, -100, 500, 500);  // Campo de fuerza con un radio de 100
    setBrush(QBrush(Qt::blue, Qt::Dense4Pattern));

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(affectEnemies()));
    timer->start(100);  // Cada 100 ms afecta a los enemigos
}

void Campo::affectEnemies() {
    // Obtener el centro del campo
    QPointF center = boundingRect().center();

    // Obtener una lista de todos los elementos colisionando con el campo
    QList<QGraphicsItem *> items = collidingItems();
    for (QGraphicsItem *item : items) {
        if (typeid(*item) == typeid(Enemigo)) {
            // Obtener la posición del enemigo
            QPointF enemyPos = item->pos();

            // Calcular el vector dirección hacia el centro del campo
            QVector2D direction(center - enemyPos);

            // Normalizar el vector dirección para obtener un vector unitario
            direction.normalize();

            // Definir la velocidad de atracción
            float attractionSpeed = 2.0f; // Puedes ajustar este valor según la velocidad deseada

            // Calcular el desplazamiento del enemigo
            QPointF displacement = direction.toPointF() * attractionSpeed;

            // Mover el enemigo hacia el centro del campo
            item->setPos(enemyPos + displacement);
        }
    }
}
