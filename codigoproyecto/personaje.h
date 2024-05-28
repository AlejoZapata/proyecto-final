#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QPixmap>
#include <QDebug>

class Personaje : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Personaje(QGraphicsItem *parent = nullptr);
    ~Personaje();
    void mover(QKeyEvent *event);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QPixmap *spriteSheet;
    int spriteX;
    int spriteY;
    int frameWidth;
    int frameHeight;
    int currentFrame;

public slots:
    void actualizarAnimacion();
};

#endif // PERSONAJE_H
