#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QWidget>
#include <QLabel>
#include <QKeyEvent>
#include <QPixmap>
#include <QTimer>

class Personaje : public QWidget {
    Q_OBJECT

public:
    explicit Personaje(QWidget *parent = nullptr);
    ~Personaje();

    void setPosicion(int x, int y);
    void mover(QKeyEvent *event);
    void actualizarAnimacion();

private:
    QLabel *spriteLabel;
    QPixmap *spriteSheet;
    int spriteX;
    int spriteY;
    int frameWidth;
    int frameHeight;
    int currentFrame;
    void actualizarPosicion();
};

#endif // PERSONAJE_H
