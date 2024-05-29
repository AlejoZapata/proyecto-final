#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Enemigo : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Enemigo(bool shouldMove, QGraphicsItem *parent = nullptr);
public slots:
    void move();
private:
    float vx;
    bool shouldMove;
};

#endif // ENEMIGO_H
