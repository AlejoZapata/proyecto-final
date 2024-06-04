#include "enemigo2.h"
#include <QTimer>
#include <QGraphicsScene>

Enemigo2::Enemigo2(QGraphicsItem *parent) : Enemigo(false, parent) {
    int newWidth = 250;
    int newHeight = 250;

    sprites.clear();
    for (int i = 0; i <= 9; i++) {
        QString imagePath = QString(":enemigo2/enem/Run/%0.png").arg(i);
        QPixmap pixmap(imagePath);
        QPixmap scaledPixmap = pixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio);
        sprites.append(scaledPixmap);
    }

    setPixmap(sprites.at(spriteIndex));

    setPos(-150, 300);
}
