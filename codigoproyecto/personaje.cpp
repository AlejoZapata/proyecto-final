#include "personaje.h"

Personaje::Personaje(QGraphicsItem *parent) :
    QObject(),
    QGraphicsPixmapItem(parent),
    spriteX(0),
    spriteY(0),
    frameWidth(64),  // Ajusta al ancho de cada frame de tu sprite
    frameHeight(64), // Ajusta al alto de cada frame de tu sprite
    currentFrame(0)
{
    spriteSheet = new QPixmap("C:/Users/juana/Downloads/Viking1walk.png");  // Asegúrate de que la ruta del recurso sea correcta
    if (!spriteSheet->isNull()) {
        setPixmap(spriteSheet->copy(0, 0, frameWidth, frameHeight));
    } else {
        qWarning() << "Error: No se pudo cargar la hoja de sprites.";
    }
    setPos(spriteX, spriteY);
}

Personaje::~Personaje() {
    delete spriteSheet;
}

void Personaje::mover(QKeyEvent *event) {
    int paso = 10;  // cantidad de píxeles que se moverá el sprite
    switch(event->key()) {
    case Qt::Key_W:
        spriteY -= paso;
        break;
    case Qt::Key_S:
        spriteY += paso;
        break;
    case Qt::Key_A:
        spriteX -= paso;
        break;
    case Qt::Key_D:
        spriteX += paso;
        break;
    default:
        break;
    }
    setPos(spriteX, spriteY);
}

void Personaje::actualizarAnimacion() {
    currentFrame = (currentFrame + 1) % 10; // Asumiendo que hay 10 frames en la animación
    int frameX = currentFrame * frameWidth;
    if (!spriteSheet->isNull()) {
        setPixmap(spriteSheet->copy(frameX, 0, frameWidth, frameHeight));
    } else {
        qWarning() << "Error: No se pudo actualizar la animación porque la hoja de sprites no se cargó correctamente.";
    }
}

void Personaje::keyPressEvent(QKeyEvent *event) {
    mover(event);
}
