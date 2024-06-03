#include "enemigo2.h"
#include <QTimer>
#include <QGraphicsScene>

Enemigo2::Enemigo2(QGraphicsItem *parent) : Enemigo(false, parent) {
    QPixmap originalPixmap(":enemigos/enem/enemigo2");
    QPixmap scaledPixmap = originalPixmap.scaled(250, 250, Qt::KeepAspectRatio);
    setPixmap(scaledPixmap);


    setPos(-150, 300);
}
