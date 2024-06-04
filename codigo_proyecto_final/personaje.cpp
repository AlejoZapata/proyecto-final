#include "personaje.h"
#include "flecha.h"
#include "antorcha.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QTimer>
#include "Personaje.h"
#include <QTimer>

Personaje::Personaje(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent), shootDirectionRight(true), canShoot(true), isAnimating(false), isShootingAnimating(false), spriteIndex(0), shootingSpriteIndex(0) {


    int newWidth = 300;
    int newHeight = 300;


    for (int i = 0; i <= 9; i++) {
        QString imagePath = QString(":personaje/Run/%0").arg(i);
        QPixmap pixmap(imagePath);
        QPixmap scaledPixmap = pixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio);
        sprites.append(scaledPixmap);
    }


    for (int i = 0; i <= 9; i++) {
        QString imagePath = QString(":personajeAt/Attack1H/%0").arg(i);
        QPixmap pixmap(imagePath);
        QPixmap scaledPixmap = pixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio);
        shootingSprites.append(scaledPixmap);
    }

    setPixmap(sprites[0]);

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &Personaje::animateMovement);

    shootingAnimationTimer = new QTimer(this);
    shootingAnimationTimer->setSingleShot(false);
    connect(shootingAnimationTimer, &QTimer::timeout, this, &Personaje::animateShooting);

    stopShootingAnimationTimer = new QTimer(this);
    stopShootingAnimationTimer->setSingleShot(true);
    connect(stopShootingAnimationTimer, &QTimer::timeout, this, &Personaje::stopShootingAnimation);
}

void Personaje::stopShootingAnimation() {
    isShootingAnimating = false;
    shootingAnimationTimer->stop();
}
void Personaje::animateMovement() {
    setPixmap(sprites[spriteIndex]);
    spriteIndex = (spriteIndex + 1) % sprites.size();
}
void Personaje::animate() {
    if (isAnimating) {
        setPixmap(shootingSprites[spriteIndex]);
    } else {
        setPixmap(sprites[spriteIndex]);
    }
    spriteIndex = (spriteIndex + 1) % sprites.size();
}
void Personaje::animateShooting() {
    setPixmap(shootingSprites[shootingSpriteIndex]);
    shootingSpriteIndex = (shootingSpriteIndex + 1) % shootingSprites.size();
}

void Personaje::shootFlecha() {
    if (canShoot) {
        Flecha *flecha = new Flecha(shootDirectionRight);
        flecha->setPos(x() + pixmap().width() / 2, y() + pixmap().height() / 2);
        scene()->addItem(flecha);

        shootDirectionRight = !shootDirectionRight;
        canShoot = false;

        QTimer::singleShot(1000, this, &Personaje::enableShoot);

        isShootingAnimating = true;
        shootingAnimationTimer->start(100);
        stopShootingAnimationTimer->start(1000);
    }
}

void Personaje::shootAntorcha() {
    if (canShoot) {
        Antorcha *antorcha = new Antorcha();
        antorcha->setPos(x() + pixmap().width() / 2, y() + pixmap().height() / 2);
        scene()->addItem(antorcha);

        if (shootDirectionRight) {
            antorcha->setInitialVelocityWithAngle(60, 45);
        } else {
            antorcha->setInitialVelocityWithAngle(60, 135);
        }

        shootDirectionRight = !shootDirectionRight;
        canShoot = false;

        QTimer::singleShot(1000, this, &Personaje::enableShoot);

        isShootingAnimating = true;
        shootingAnimationTimer->start(100);
        stopShootingAnimationTimer->start(1000);
    }
}

void Personaje::enableShoot() {
    canShoot = true;
}
