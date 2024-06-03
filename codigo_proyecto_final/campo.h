#ifndef CAMPO_H
#define CAMPO_H

#include <QGraphicsEllipseItem>
#include <QObject>
#include "Personaje.h"

class Campo : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
public:
    explicit Campo(Personaje *personaje, QGraphicsItem *parent = nullptr);
private:
    Personaje *personaje;
signals:
    void enemyReachedMidpoint();
public slots:
    void affectEnemies();

};

#endif // CAMPO_H
