#include "casa.h"

Casa::Casa(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap(":casa/casa/casa1").scaled(200, 200));
}
