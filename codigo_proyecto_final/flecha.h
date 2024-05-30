#ifndef FLECHA_H
#define FLECHA_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Flecha : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Flecha(bool directionRight, QGraphicsItem *parent = nullptr);
public slots:
    void move();
private:
    bool directionRight;
};

#endif // FLECHA_H
