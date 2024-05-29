#ifndef FLECHA_H
#define FLECHA_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Flecha : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Flecha(QGraphicsItem *parent = nullptr);
public slots:
    void move();
};

#endif // FLECHA_H
