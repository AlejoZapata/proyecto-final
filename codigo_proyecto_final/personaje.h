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
    QList<QPixmap> sprites;
    int spriteIndex = 0;
private slots:
    void enableShoot();
private:
    bool shootDirectionRight;
    bool canShoot;
};

#endif // PERSONAJE_H
