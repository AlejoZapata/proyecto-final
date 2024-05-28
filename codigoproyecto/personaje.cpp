#include "personaje.h"

Personaje::Personaje(QWidget *parent) :
    QWidget(parent),
    spriteX(0),
    spriteY(0),
    frameWidth(64),  // Ajusta al ancho de cada frame de tu sprite
    frameHeight(64), // Ajusta al alto de cada frame de tu sprite
    currentFrame(0)
{
    spriteLabel = new QLabel(this);  // Asegúrate de que el QLabel tenga `this` como padre
    spriteSheet = new QPixmap(":/Viking1walk.png");  // Asegúrate de que la ruta del recurso sea correcta
    spriteLabel->setPixmap(spriteSheet->copy(0, 0, frameWidth, frameHeight));
}

Personaje::~Personaje() {
    delete spriteSheet;
    // No es necesario eliminar spriteLabel, ya que se eliminará automáticamente al eliminar el padre (this)
}

void Personaje::setPosicion(int x, int y) {
    spriteX = x;
    spriteY = y;
    actualizarPosicion();
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
            QWidget::keyPressEvent(event);
    }
    actualizarPosicion();
}

void Personaje::actualizarPosicion() {
    spriteLabel->move(spriteX, spriteY);
}

void Personaje::actualizarAnimacion() {
    currentFrame = (currentFrame + 1) % 10; // Asumiendo que hay 10 frames en la animación
    int frameX = currentFrame * frameWidth;
    spriteLabel->setPixmap(spriteSheet->copy(frameX, 0, frameWidth, frameHeight));
}
