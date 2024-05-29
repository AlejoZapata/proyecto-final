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

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // PERSONAJE_H
