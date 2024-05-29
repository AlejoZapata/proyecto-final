#include "casa.h"

Casa::Casa(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap("C:/Users/juana/Downloads/casaaldea-removebg-preview.png").scaled(200, 200));
}
