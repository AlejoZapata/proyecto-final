#include "enemigo2.h"
#include <QTimer>
#include <QGraphicsScene>

Enemigo2::Enemigo2(QGraphicsItem *parent) : Enemigo(false, parent) {
    QPixmap originalPixmap("C:/Users/juana/Downloads/Vikings/Viking3/Walk/7.png");
    QPixmap scaledPixmap = originalPixmap.scaled(500, 500, Qt::KeepAspectRatio);
    setPixmap(scaledPixmap);


    setPos(-150, 100);
}
