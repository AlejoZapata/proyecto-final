#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QGraphicsPixmapItem>
#include <QObject>


class Enemigo : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Enemigo(bool shouldMove, QGraphicsItem *parent = nullptr);
    void animate();
signals:
    void enemyOutOfBounds();
public slots:
    void move();
protected:
    QList<QPixmap> sprites;
    float vx;
    bool shouldMove;
    int spriteIndex;
};

#endif // ENEMIGO_H
