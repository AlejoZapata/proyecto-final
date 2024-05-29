#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Enemigo : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Enemigo(QGraphicsItem *parent = nullptr);
public slots:
    void move();
private:

    float vx;
};

#endif // ENEMIGO_H
