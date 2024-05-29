#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Personaje : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Personaje(QGraphicsItem *parent = nullptr);
    void shootFlecha();
    void shootAntorcha();
};

#endif // PERSONAJE_H
