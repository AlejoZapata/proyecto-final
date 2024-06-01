#ifndef CAMPO_H
#define CAMPO_H

#include <QGraphicsEllipseItem>
#include <QObject>

class Campo : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
public:
    Campo(QGraphicsItem *parent = nullptr);
signals:
    void enemyReachedMidpoint();
public slots:
    void affectEnemies();
};

#endif // CAMPO_H
