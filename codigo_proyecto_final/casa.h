#ifndef CASA_H
#define CASA_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Casa : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Casa(QGraphicsItem *parent = nullptr);
};

#endif // CASA_H
