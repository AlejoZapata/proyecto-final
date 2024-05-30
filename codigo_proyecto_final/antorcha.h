#ifndef ANTORCHA_H
#define ANTORCHA_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Antorcha : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Antorcha(QGraphicsItem *parent = nullptr);
    void setInitialVelocity(float vx, float vy);
    void setInitialVelocityWithAngle(float velIn, float theta);
public slots:
    void move();
private:
    float vx, vy;
    float t;
    float g;
};

#endif // ANTORCHA_H
