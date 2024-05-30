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
    void animateMovement();
    void animateShooting();
    void stopShootingAnimation();
    QList<QPixmap> sprites;
    QList<QPixmap> shootingSprites;
    int spriteIndex = 0;
    int shootingSpriteIndex = 0;
    bool isAnimating = false;
    bool isShootingAnimating = false;
    QTimer *animationTimer;
    QTimer *shootingAnimationTimer;
    QTimer *stopShootingAnimationTimer;
    bool shootDirectionRight;
    bool canShoot;
private slots:
    void enableShoot();
public slots:
    void animate();
};

#endif // PERSONAJE_H
